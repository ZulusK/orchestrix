#ifndef ORCHESTRIX_AUDIOPLAYER_H
#define ORCHESTRIX_AUDIOPLAYER_H

#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/OpenAL.h>
#include <thread>
#include <mutex>


/**
 * Audio player, which stored info about source
 * and source, buffers and current state
*/
class AudioPlayer {
    AudioManager *manager;
    AudioSource *source;
    ALvoid *sound;
    ALsizei currPos;
    ALenum state;
    int remainBuffers;
    //al settings
    AudioInfo info;
    //source settings
    PlayerInfo settings;
    //mutex to read data
    recursive_mutex _readDataMutex;
    recursive_mutex _setBuffCntMutex;
private:

    bool fillBuffer(AudioBuffer *buffer);

    void update();

    void exec(thread **runningThread);
public:
    AudioPlayer(AudioManager *manager, AudioData *sound, float volume);

    ~AudioPlayer();

    void play();

    void pause();

    void stop();

    bool isPlaying();

    void updateState();

    string toString();

    void updateBuffer(AudioBuffer *buffer);
};

#endif //ORCHESTRIX_AUDIOPLAYER_H
