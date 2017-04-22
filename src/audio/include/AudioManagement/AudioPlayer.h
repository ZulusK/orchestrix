//
// Created by zulus on 22.04.17.
//

#ifndef ORCHESTRIX_AUDIOPLAYER_H
#define ORCHESTRIX_AUDIOPLAYER_H


#include <AL/al.h>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>
#include <jmorecfg.h>
#include "Entity.h"


class AudioPlayer {
    AudioData *data;
    ALenum state;
    ALenum format;
    ALsizei frequency;
    SoundSource *source;
    float pitch;
    float gain;
    ALboolean loop;
    vector3f pos;
    vector3f vel;
    int remainBuffers;
    ALsizei currPos;
private:
    void update();

    boolean preloadBuffer(ALuint buff);

public:
    ALenum getFormat() const;

    ALuint getFrequency() const;

    SoundSource *getSource() const;

    ALenum getState() const;

    float getPitch() const;

    float getGain() const;

    ALboolean isLoop() const;

    const vector3f &getPos() const;

    const vector3f &getVel() const;

    AudioPlayer(AudioData *data, SoundSource *source);

    virtual ~AudioPlayer();

    AudioData *getData() const;

    void play();

    void stop();
};


#endif //ORCHESTRIX_AUDIOPLAYER_H
