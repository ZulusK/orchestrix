//
// Created by zulus on 23.04.17.
//
#include <AudioManagement/AudioPlayer.h>
#include <AudioManagement/OpenAL.h>
#include <thread>

/**
 * convert not Al-format data to ALenum
 * @param channels count of channels
 * @param bitsPerSample bitser sample (eq. 16 or 8)
 * @return ALenum for presentetive foram
 */
ALenum toALformat(int channels, int bitsPerSample) {
    if (channels == 2) {
        if (bitsPerSample == 16) {
            return AL_FORMAT_STEREO16;
        } else if (bitsPerSample == 8) {
            return AL_FORMAT_STEREO8;
        }
    } else if (channels == 1) {
        if (bitsPerSample == 16) {
            return AL_FORMAT_MONO16;
        } else if (bitsPerSample == 8) {
            return AL_FORMAT_MONO8;
        }
    }
    return AL_ILLEGAL_ENUM;
}

/**
 * create new player
 * @param manager reference to AudioManager, which is stored AudioPlayer
 * @param sound reference to sound data
 * @param volume volume of player
 * @param id id of player
 */
AudioPlayer::AudioPlayer(AudioManager *manager, AudioData *sound, float volume) {
    //copy references
    this->sound = sound->get_source();
    this->info.samples = sound->get_size();
    this->info.format = toALformat(sound->get_channels(), sound->get_bitsPerSample());
    this->info.frequency = sound->get_sampleRate();
    this->settings.pos.x = 0;
    this->settings.pos.y = 0;
    this->settings.pos.z = 0;
    this->settings.vel.x = 0;
    this->settings.vel.y = 0;
    this->settings.vel.z = 0;
    this->settings.pitch = 1;
    this->settings.gain = volume;
    this->manager = manager;
    this->state = AL_STOPPED;
    this->remainBuffers = 0;
    this->currPos = 0;
    this->source = manager->getFreeSource();
}

bool AudioPlayer::isPlaying() {
    return state == AL_PLAYING;
}

/**
 * fills buffer by sound's data
 * @param buffer reference to AudioBuffer
 * @return is buffer filled
 */
bool AudioPlayer::fillBuffer(AudioBuffer *buffer) {
    if (buffer) {
        if (currPos >= info.samples) {
            return false;
        }
        ALsizei nextChunk = min(BUFFER_SIZE, info.samples - currPos);
        if (info.format == AL_FORMAT_STEREO16 || info.format == AL_FORMAT_MONO16) {
            alBufferData(buffer->refID, info.format, (__int16_t *) sound + currPos, nextChunk, info.frequency);
        } else {
            alBufferData(buffer->refID, info.format, (__int8_t *) sound + currPos, nextChunk, info.frequency);
        }
        currPos += nextChunk + 1;
        return true;
    }
    return false;
}

void AudioPlayer::updateState() {
    alGetSourcei(source->refID, AL_SOURCE_STATE, &state);
}

void AudioPlayer::update() {
    updateState();
    if (this->state != AL_PLAYING) {
        //sound is not playing  (PAUSED / STOPPED) do not update
        return;
    }
    int buffersProcessed = 0;
    AL_CHECK(alGetSourcei(this->source->refID, AL_BUFFERS_PROCESSED, &buffersProcessed));
    // check to see if we have a buffer to deQ
    if (buffersProcessed > 0) {
        if (buffersProcessed > 1) {
            //we have processed more than 1 buffer since last call of Update method
            //we should probably reload more buffers than just the one (not supported yet)
            //todo
        }
        // remove the buffer form the source
        AudioBuffer processedBuffer;
        AL_CHECK(alSourceUnqueueBuffers(this->source->refID, 1, &processedBuffer.refID));
        // fill the buffer up and reQ!
        // if we cant fill it up then we are finished
        // in which case we dont need to re-Q
        // return NO if we dont have more buffers to Q
        updateState();
        if (this->state == AL_STOPPED) {
            //put it back - sound is not playing anymore
            AL_CHECK(alSourceQueueBuffers(this->source->refID, 1, &processedBuffer.refID));
            return;
        }
        //call method to load data to buffer
        //see method in section - Creating sound
        if (this->fillBuffer(&processedBuffer) == false) {
            this->remainBuffers--;
        }
        //put the newly filled buffer back (at the end of the queue)
        AL_CHECK(alSourceQueueBuffers(this->source->refID, 1, &processedBuffer.refID));
    }

    if (this->remainBuffers <= 0) {
        //no more buffers remain - stop sound automatically
        stop();
    }
}

void AudioPlayer::startPlaying(thread ** runningThread) {
    AL_CHECK(alSourcef(this->source->refID, AL_PITCH, this->settings.pitch));
    AL_CHECK(alSourcef(this->source->refID, AL_GAIN, this->settings.gain));
    AL_CHECK(alSource3f(this->source->refID, AL_POSITION, this->settings.pos.x, this->settings.pos.y,
                        this->settings.pos.z));
    AL_CHECK(alSource3f(this->source->refID, AL_VELOCITY, this->settings.vel.x, this->settings.vel.y,
                        this->settings.vel.z));
    {
        bool process = true;
        int i = 0;
        for (AudioBuffer *buff = manager->getFreeBuffer();
             process && i < MAX_BUFFER_PER_PLAYER && buff != NULL;
             i++, buff = manager->getFreeBuffer()) {
            process = fillBuffer(buff);
            cout << "created " << buff->refID << endl;
            alSourceQueueBuffers(this->source->refID, 1, &buff->refID);

        }
        remainBuffers = i - 1;
    }
    AL_CHECK(alSourcePlay(source->refID));
    alGetSourcei(source->refID, AL_SOURCE_STATE, &state);
    cout << "checkable" << endl;
    while (state == AL_PLAYING) {
        update();
    }
    delete *runningThread;
}

void AudioPlayer::play() {
    thread * playerThread;
    playerThread=new thread(&AudioPlayer::startPlaying, this, &playerThread);
}

void AudioPlayer::stop() {
    AL_CHECK(alSourceStop(source->refID));
}

AudioPlayer::~AudioPlayer() {
    if (isPlaying()) {
        stop();
    }
}