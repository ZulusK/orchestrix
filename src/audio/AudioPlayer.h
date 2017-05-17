#ifndef ORCHESTRIX_AUDIOPLAYER_H
#define ORCHESTRIX_AUDIOPLAYER_H

#include <AudioData.h>
#include <AudioManager.h>
#include <OpenAL.h>
#include <mutex>
#include <thread>

enum { PLAYING, STOPPED, PAUSED };
#define SLEEP_TIME 100
typedef chrono::high_resolution_clock Clock;
/**
 * Audio player, which stored info about source
 * and source, buffers and current state
*/
class AudioPlayer {
  long playingTime;
  AudioManager *manager;
  thread *runningThread;
  ALuint source;
  ALvoid *rawSoundData;
  int currState;
  ALsizei currPos;
  ALenum state;
  int remainBuffers;
  // al settings
  AudioInfo info;
  // source settings
  PlayerInfo settings;
  // mutex to read data
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
  AudioPlayer(AudioManager *manager, AudioData *audioData, float volume = 1);

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

  double getTime();
};

#endif // ORCHESTRIX_AUDIOPLAYER_H
