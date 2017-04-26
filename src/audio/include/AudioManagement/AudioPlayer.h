#ifndef ORCHESTRIX_AUDIOPLAYER_H
#define ORCHESTRIX_AUDIOPLAYER_H

#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/OpenAL.h>
#include <thread>
#include <mutex>

enum {
    PLAYING,
    STOPPED,
    PAUSED
};

/**
 * Audio player, which stored info about source
 * and source, buffers and current state
*/
class AudioPlayer {
    AudioManager *manager;
    thread * runningThread;
    ALuint source;
    ALvoid *rawSoundData;
    int currState;
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

    bool play();

    void pause();

    bool rewind();

    void stop();

    bool isPlaying();

    string toString();

    bool isStopped();

    bool isPaused();

    void useSettigs();
};

#endif //ORCHESTRIX_AUDIOPLAYER_H
