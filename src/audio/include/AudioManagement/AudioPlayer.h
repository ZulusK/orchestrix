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
    ALuint source;
    ALvoid *rawSoundData;
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
    recursive_mutex _updateStateMutex;
private:

    bool fillBuffer(ALuint buffer);

    void update();

    void exec();

    void updateBuffer(ALuint buffer);

    bool preload();

    void freeResources();

    void updateState();
public:
    AudioPlayer(AudioManager *manager, AudioData *audioData, float volume);

    ~AudioPlayer();

    thread *play();

    void pause();

    void stop();

    bool isPlaying();

    string toString();

    bool isStopped();

    bool isPaused();
};

#endif //ORCHESTRIX_AUDIOPLAYER_H
