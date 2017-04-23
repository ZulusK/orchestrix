//
// Created by zulus on 23.04.17.
//
#include <AudioManagement/AudioPlayer.h>

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
AudioPlayer::AudioPlayer(AudioManager *manager, AudioData *sound, float volume){
    //copy references
    this->sound = sound->get_source();
    this->samples = sound->get_size();
    this->format = toALformat(sound->get_channels(), sound->get_bitsPerSample());
    this->frequency = sound->get_sampleRate();
    this->pos.x = 0;
    this->pos.y = 0;
    this->pos.z = 0;
    this->vel.x = 0;
    this->vel.y = 0;
    this->vel.z = 0;
    this->pitch = 1;
    this->gain = volume;
    this->manager = manager;
    this->state = AL_STOPPED;
    this->remainBuffers = -1;
    this->remainBuffers = 0;
    this->source = NULL;
}

bool AudioPlayer::isPlaying() {

    return state == AL_PLAYING;
}