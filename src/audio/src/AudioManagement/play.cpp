////
//// Created by zulus on 22.04.17.
////
//
//#include <AudioManagement/AudioManager.h>
//#include <iostream>
//#include <AL/alut.h>
//
//#ifndef AL_CHECK
//#ifdef _DEBUG
//#define AL_CHECK(stmt) do { \
//            stmt; \
//            CheckOpenALError(); \
//        } while (0);
//#else
//#define AL_CHECK(stmt) stmt
//#endif
//#endif
//
//#define MAX_BUFFER_LEN 256*256
//
//using namespace std;
//
//ALenum to_al_format(int channels, int bitsPerSample) {
//    if (channels == 2) {
//        if (bitsPerSample == 16) {
//            return AL_FORMAT_STEREO16;
//        } else if (bitsPerSample == 8) {
//            return AL_FORMAT_STEREO8;
//        }
//    } else {
//        if (bitsPerSample == 16) {
//            return AL_FORMAT_MONO16;
//        } else if (bitsPerSample == 8) {
//            return AL_FORMAT_MONO8;
//        }
//    }
//    return -1;
//}
//
//ALuint min(size_t a, size_t b) {
//    return (a < b) ? a : b;
//}
//
//
//AudioPlayer::AudioPlayer(AudioManager *manager, AudioData *data, int reservedBuffers) {
//    this->data = data;
//    this->gain = 1.0;
//    this->pitch = 1.0;
//    this->loop = false;
//    this->format = to_al_format(data->get_channels(), data->get_bitsPerSample());
//    this->frequency = data->get_sampleRate();
//    //
//    this->vel.x = 0;
//    this->vel.y = 0;
//    this->vel.z = 0;
//    //
//    this->pos.x = 0;
//    this->pos.y = 0;
//    this->pos.z = 0;
//    this->currPos = 0;
//    this->remainBuffers = reservedBuffers;
//    this->source = manager->getFreeSource();
//}
//
//AudioPlayer::~AudioPlayer() {
//
//}
//
//int AudioPlayer::getState() const {
//    return state;
//}
//
//float AudioPlayer::getPitch() const {
//    return pitch;
//}
//
//float AudioPlayer::getGain() const {
//    return gain;
//}
//
//ALboolean AudioPlayer::isLoop() const {
//    return loop;
//}
//
//const vector3f &AudioPlayer::getPos() const {
//    return pos;
//}
//
//const vector3f &AudioPlayer::getVel() const {
//    return vel;
//}
//
//ALenum AudioPlayer::getFormat() const {
//    return format;
//}
//
//ALuint AudioPlayer::getFrequency() const {
//    return frequency;
//}
//
//SoundSource *AudioPlayer::getSource() const {
//    return source;
//}
//
//AudioData *AudioPlayer::getData() const {
//    return data;
//}
//
//bool AudioPlayer::preloadBuffer(ALuint buff) {
//    ALsizei nextChunk = min(MAX_BUFFER_LEN, data->get_size() - currPos);
//    if (nextChunk + currPos <= data->get_size()) {
//        cout << currPos << "->" << currPos + nextChunk << endl;
//        cout << "fill buffer " << buff << endl;
//        if (format == AL_FORMAT_STEREO16 || format == AL_FORMAT_MONO16) {
//            alBufferData(buff, format, (__int16_t *) this->data->get_source() + currPos, nextChunk, frequency);
//        } else {
//            alBufferData(buff, format, (__int8_t *) this->data->get_source() + currPos, nextChunk, frequency);
//        }
//        currPos += nextChunk;
//        return true;
//    } else {
//        return false;
//    }
//
//}
//
//void AudioPlayer::play() {
//    alSourcef(source->refID, AL_PITCH, pitch);
//// check for errors
//    alSourcef(source->refID, AL_GAIN, gain);
//// check for errors
//    alSource3f(source->refID, AL_POSITION, pos.x, pos.y, pos.z);
//// check for errors
//    alSource3f(source->refID, AL_VELOCITY, vel.x, vel.y, vel.z);
//
//    for (int i = 0; i < remainBuffers; i++) {
//        preloadBuffer(source->buffers[i]->refID);
//        alSourceQueueBuffers(this->source->refID, 1, &source->buffers[i]->refID);
//    }
//
//    alSourcePlay(source->refID);
//    ALint state;
//    alGetSourcei(source->refID, AL_SOURCE_STATE, &state);
//    while (state == AL_PLAYING || state == AL_PAUSED) {
//        update();
//
//    }
//}
//
//
//void AudioPlayer::update() {
//    alGetSourcei(source->refID, AL_SOURCE_STATE, &state);
//    if (this->state != AL_PLAYING) {
//        //rawBytes is not playing  (PAUSED / STOPPED) do not update
//        return;
//    }
//    int buffersProcessed = 0;
//    alGetSourcei(this->source->refID, AL_BUFFERS_PROCESSED, &buffersProcessed);
////    cout<<"buffer processed "<<buffersProcessed<<endl;
//    // check to see if we have a buffer to deQ
//    if (buffersProcessed > 0) {
//        ALuint bufferID;
//        alSourceUnqueueBuffers(this->source->refID, 1, &bufferID);
//
//        // fill the buffer up and reQ!
//        // if we cant fill it up then we are finished
//        // in which case we dont need to re-Q
//        // return NO if we dont have more buffers to Q
//        alGetSourcei(source->refID, AL_SOURCE_STATE, &state);
//        if (this->state == AL_STOPPED) {
//            //put it back - rawBytes is not playing anymore
//            alSourceQueueBuffers(this->source->refID, 1, &bufferID);
//            return;
//        }
//        //call method to load data to buffer
//        //see method in section - Creating rawBytes
//        if (this->preloadBuffer(bufferID) == false) {
//            this->remainBuffers--;
//        }
//        //put the newly filled buffer back (at the end of the queue)
//        alSourceQueueBuffers(this->source->refID, 1, &bufferID);
//    }
//    if (this->remainBuffers <= 0) {
//        cout << "stop" << endl;
//        //no more buffers remain - stop rawBytes automatically
//        this->stop();
//    }
//}
//
//void AudioPlayer::stop() {
//    alSourceStop(source->refID);
//}
//
//void AudioPlayer::freeBuffer(SoundBuffer *buff) {
//
//    freeBuffers.push_back(buff->refID);
//}
//
//ALuint getFreeBuffer() {
//    SoundBuffer *buffer =
//}