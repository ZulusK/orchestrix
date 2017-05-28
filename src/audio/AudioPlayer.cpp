#include <audio/AudioPlayer.h>
#include <audio/OpenAL.h>
#include <thread>

/**
 * create new player
 * @param manager reference to AudioManager, which is stored AudioPlayer
 * @param audioData reference to sound data
 * @param volume volume of player
 * @param id id of player
 */
AudioPlayer::AudioPlayer(AudioManager *manager, AudioData *audioData,
                         float volume) {
  // copy references
  this->rawSoundData = audioData->get_source();
  this->info.samples = audioData->get_size();
  this->info.format =
      toALformat(audioData->get_channels(), audioData->get_bitsPerSample());
  this->info.frequency = audioData->get_sampleRate();
  this->runningThread = NULL;
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
  this->currState = STOPPED;
  this->remainBuffers = 0;
  this->currPos = 0;
  this->source = manager->getFreeSource();
}

/**
 * fills buffer by sound's data
 * @param buffer reference to buffer
 * @return is all buffer filled
 */
bool AudioPlayer::fillBuffer(ALuint buffer) {
  if (buffer > 0) {
    if (currPos < info.samples) {
      _readDataMutex.lock();
      ALsizei nextChunk = std::min(BUFFER_SIZE, info.samples - currPos);
      if (info.format == AL_FORMAT_STEREO16 ||
          info.format == AL_FORMAT_MONO16) {
        AL_CHECK(alBufferData(buffer, info.format,
                              (ALbyte *)rawSoundData + currPos, nextChunk,
                              info.frequency));
      } else {
        AL_CHECK(alBufferData(buffer, info.format,
                              (ALbyte *)rawSoundData + currPos, nextChunk,
                              info.frequency));
      }
      currPos += nextChunk;
      _readDataMutex.unlock();
      return false;
    }
  }
  return true;
}

void AudioPlayer::update() {
  updateState();
  if (this->state != AL_PLAYING) {
    /*
     * rawBytes is not playing  (PAUSED / STOPPED) do not update
     */
    return;
  }
  int countOfProcessedBuffer = 0;
  AL_CHECK(alGetSourcei(source, AL_BUFFERS_PROCESSED, &countOfProcessedBuffer));
  /*
   * check to see if we have a buffer to deQ
   */
  for (int i = 0; i < countOfProcessedBuffer; i++) {
    /*
     * remove the buffer from the source
    */
    ALuint processedBuffer;
    AL_CHECK(alSourceUnqueueBuffers(source, 1, &processedBuffer));
    /*
     * fill the buffer up and reQ!
     * if we cant fill it up then we are finished
     * in which case we dont need to re-Q
     * return NO if we dont have more buffers to Q
     */
    updateState();
    if (this->state == AL_STOPPED) {
      AL_CHECK(alSourceQueueBuffers(source, 1, &processedBuffer));
      return;
    }
    /*
     * call method to load data to buffer
    */
    manager->clearBuffer(processedBuffer);
    ALuint newBuffer = manager->getFreeBuffer();
    if (fillBuffer(newBuffer)) {
      remainBuffers--;
      if (this->remainBuffers <= 0) {
        stop();
      }
    } else {
      AL_CHECK(alSourceQueueBuffers(source, 1, &newBuffer));
    }
  }
}

void AudioPlayer::updateState() {
  _updateStateMutex.lock();
  AL_CHECK(alGetSourcei(source, AL_SOURCE_STATE, &state));
  _updateStateMutex.unlock();
}

bool AudioPlayer::preload() {
  _setBuffCntMutex.lock();
  remainBuffers = 0;
  currPos = 0;
  bool isAllSoundLoaded = false;
  std::vector<ALuint> loadedBuffers;
  while (loadedBuffers.size() < MAX_BUFFER_PER_PLAYER && !isAllSoundLoaded) {
    ALuint buff = manager->getFreeBuffer();
    isAllSoundLoaded = fillBuffer(buff);
    if (!isAllSoundLoaded) {
      loadedBuffers.push_back(buff);
    }
  };
  remainBuffers = loadedBuffers.size();
  ALuint buffArr[remainBuffers];
  for (int i = 0; i < remainBuffers; i++) {
    buffArr[i] = loadedBuffers[i];
  }
  AL_CHECK(alSourceQueueBuffers(source, remainBuffers, buffArr));
  _setBuffCntMutex.unlock();
  return remainBuffers;
}

/**
 * free used resources and buffers
 */
void AudioPlayer::freeResources() {
  _setBuffCntMutex.lock();
  updateState();
  if (state == AL_PLAYING) {
    stop();
  }
  int buffersProcessed = 0;
  AL_CHECK(alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffersProcessed));
  ALuint processedBuffer;
  for (int i = 0; i < buffersProcessed; i++) {
    AL_CHECK(alSourceUnqueueBuffers(source, 1, &processedBuffer));
    manager->clearBuffer(processedBuffer);
  }
  manager->clearSource(source);
  rawSoundData = NULL;
  _setBuffCntMutex.unlock();
}

void AudioPlayer::useSettigs() {
  AL_CHECK(alSourcef(source, AL_PITCH, settings.pitch));
  AL_CHECK(alSourcef(source, AL_GAIN, settings.gain));
  AL_CHECK(alSource3f(source, AL_POSITION, settings.pos.x, settings.pos.y,
                      settings.pos.z));
  AL_CHECK(alSource3f(source, AL_VELOCITY, settings.vel.x, settings.vel.y,
                      settings.vel.z));
}

void AudioPlayer::exec() {
  updateState();
  playingTime = 0;
  auto time0 = Clock::now();
  while (currState == PLAYING && state == AL_PLAYING) {
    update();
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    playingTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                      Clock::now() - time0)
                      .count();
  }
  updateState();
  playingTime = 0;
}

/**
 * try to run playing sound, if it's not playing yet
 * @return true, if success
 */
bool AudioPlayer::play() {
  if (this->state != AL_PLAYING && this->rawSoundData) {
    this->currState = PLAYING;
    this->currPos = 0;
    if (!preload()) {
      return false;
    }
    useSettigs();
    AL_CHECK(alSourcePlay(source));
    this->runningThread = new std::thread(&AudioPlayer::exec, this);
    return true;
  } else
    return false;
}

long AudioPlayer::getTime() { return playingTime; }

bool AudioPlayer::rewind() {
  if (isPaused()) {
    this->currState = PLAYING;
    AL_CHECK(alSourcePlay(source));
    updateState();
    this->runningThread = new std::thread(&AudioPlayer::exec, this);
    return true;
  }
  return false;
}

void AudioPlayer::pause() {
  if (isPlaying() && this->runningThread) {
    AL_CHECK(alSourcePause(source));
    currState = PAUSED;
    updateState();
    this->runningThread->join();
    delete runningThread;
    runningThread = NULL;
  }
}

void AudioPlayer::stop() {
  if (!isStopped()) {
    AL_CHECK(alSourceStop(source));
    ALint processedBuffers;
    AL_CHECK(alGetSourcei(source, AL_BUFFERS_PROCESSED, &processedBuffers));
    for (int i = 0; i < processedBuffers; i++) {
      ALuint buffer;
      AL_CHECK(alSourceUnqueueBuffers(source, 1, &buffer));
      manager->clearBuffer(buffer);
    }
    currState = STOPPED;
    updateState();
    this->runningThread->join();
    delete runningThread;
    runningThread = NULL;
  }
}

AudioPlayer::~AudioPlayer() {
  stop();
  freeResources();
}

std::string AudioPlayer::toString() {
  std::string s = "AudioPlayer:\n";
  s += "------------------------------\n";
  s += "Samples: " + std::to_string(info.samples) + "\n";
  s += "Frequency: " + std::to_string(info.frequency) + "\n";
  s += "Format: ";
  if (info.format == AL_FORMAT_STEREO16) {
    s += "STEREO_16";
  } else if (info.format == AL_FORMAT_STEREO8) {
    s += "STEREO_8";
  } else if (info.format == AL_FORMAT_MONO16) {
    s += "MONO_16";
  } else if (info.format == AL_FORMAT_MONO8) {
    s += "MONO_8";
    ;
  }
  s += "\n";
  s += "State: ";
  if (state == AL_PLAYING) {
    s += "PLAYING";
  } else if (state == AL_STOPPED) {
    s += "STOPPED";
  } else {
    s += "PAUSED";
  }
  s += "\n";
  s += "RemainingBuffers: " + std::to_string(remainBuffers) + "\n";
  s += "------------------------------\n";
  return s;
}

/**
 * check is soundn playing
 * @return true,if sound  is playing now
 */
bool AudioPlayer::isPlaying() {
  return state == AL_PLAYING && currState == PLAYING;
}

bool AudioPlayer::isPaused() {
  //    updateState();
  return state == AL_PAUSED;
}

bool AudioPlayer::isStopped() {
  //    updateState();
  return state == AL_STOPPED;
}
