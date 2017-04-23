#ifndef ORCHESTRIX_AUDIOPLAYER_H
#define ORCHESTRIX_AUDIOPLAYER_H

#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/OpenAL.h>

/**
 * Audio player, which stored info about source
 * and source, buffers and current state
*/

class AudioPlayer {
    AudioManager *manager;
    AudioSource *source;
    ALvoid *sound;
    ALsizei currPos;
    int remainBuffers;
    //al settings
    ALenum state;
    ALenum format;
    ALsizei samples;
    ALint frequency;
    //source settings
    vector3f pos;
    vector3f vel;
    float pitch;
    float gain;
public:
    AudioPlayer(AudioManager * manager, AudioData *sound, float volume);

    ~AudioPlayer();

    void play();

    void pause();

    void stop();

    bool isPlaying();
};

#endif //ORCHESTRIX_AUDIOPLAYER_H
