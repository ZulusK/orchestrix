//
// Created by zulus on 13.04.17.
//

#include "AudioManagement/AudioManager.h"
#include <cstring>
#include <AudioManagement/OpenAL.h>

using namespace std;

/**
 * print all registered in system devices
 * @return vector with string
 */
std::vector<string> AudioManager::getAllDevices() {
    const char *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    const char *next = devices + 1;

    size_t len = 0;
    std::vector<string> devicesNames;

    while (devices && *devices != '\0' && next && *next != '\0') {
        string d = string(devices);
        devicesNames.push_back(d);
        len = strlen(devices);
        devices += (len + 1);
        next += (len + 2);
    }
    return devicesNames;
}

void AudioManager::deleteBuffer(ALuint buffer) {
    AL_CHECK(alDeleteBuffers(1, &buffer));
}

void AudioManager::deleteSource(ALuint source) {
    ALenum state;
    AL_CHECK(alGetSourcei(source, AL_SOURCE_STATE, &state));
    if (state != AL_PLAYING) {
        AL_CHECK(alSourceStop(source));
    }
    AL_CHECK(alDeleteSources(1, &source));
}

AudioManager::~AudioManager() {
    _bufferMutex.lock();
    _sourceMutex.lock();
    for (auto it = freeSources.begin(); it != freeBuffers.end(); it++) {
        AL_CHECK(alDeleteSources(1, &(*it)));
        freeSources.erase(it);
    }
    for (auto it = freeBuffers.begin(); it != freeBuffers.end(); it++) {
        AL_CHECK(alDeleteBuffers(1, &(*it)));
        freeBuffers.erase(it);
    }
    for (auto it = sources.begin(); it != sources.begin(); it++) {
        deleteSource(*it);
        sources.erase(it);
    }

    for (auto it = buffers.begin(); it != buffers.end(); it++) {
        deleteBuffer(*it);
        buffers.erase(it);
    }
    AL_CHECK(alcMakeContextCurrent(NULL));
    AL_CHECK(alcDestroyContext(context));
    AL_CHECK(alcCloseDevice(device));
    _bufferMutex.unlock();
    _sourceMutex.unlock();
}

/**
 * initialize AudioManager to work with current system
 * @param source count of  max source
 * @param buffer count of max buffers(
 * @return created AudioPlayer
 */
AudioManager *AudioManager::init(int source, int buffer) {
    if (source < MIN_SOURCE_COUNT || source > MAX_SOURCE_COUNT) {
        source = MIN_SOURCE_COUNT;
    }
    if (buffer < MIN_BUFFER_COUNT || buffer > MAX_BUFFER_COUNT) {
        buffer = MIN_BUFFER_COUNT;
    }
    cout << "==============================================" << endl;
    cout << "               All devices:" << endl;
    print(getAllDevices());
    cout << "=============================================" << endl;
    ALCdevice *deviceAL = alcOpenDevice(NULL);
    if (!deviceAL) {
        cout << "Failed to init OpenAL device." << endl;
        return NULL;
    }
    ALCcontext *contextAL = alcCreateContext(deviceAL, NULL);
    AL_CHECK(alcMakeContextCurrent(contextAL));
    return new AudioManager(deviceAL, contextAL, source, buffer);
}

/**
 * create new Audio Manager
 * @param device
 * @param contex
 * @param sourceCnt
 * @param bufferCnt
 */
AudioManager::AudioManager(ALCdevice *device, ALCcontext *contex, int sourceCnt, int bufferCnt) {
    this->device = device;
    this->context = contex;

    this->masterVolume = 1.0;
    //
    this->listenerPos.x = 0;
    this->listenerPos.y = 0;
    this->listenerPos.z = 0;
    //
    this->listenerVel.x = 0;
    this->listenerVel.y = 0;
    this->listenerVel.z = 1;

    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 1.0;
    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 1.0;

    //create buffers
    for (int i = 0; i < bufferCnt; i++) {
        createBuffer();
    }
    //create sources
    for (int i = 0; i < sourceCnt; i++) {
        createSource();
    }
    AL_CHECK(alcMakeContextCurrent(context));
    // check for errros
    AL_CHECK(alListener3f(AL_POSITION, listenerPos.x, listenerPos.y, listenerPos.z));
    // check for errors
    AL_CHECK(alListener3f(AL_VELOCITY, listenerVel.x, listenerVel.y, listenerVel.z));
    // check for errors
    AL_CHECK(alListenerfv(AL_ORIENTATION, listenerOri));
}

/**
 * generate new buffer
 * @return created buffer
 */
ALuint AudioManager::generateBuffer() {
    ALuint buff;
    AL_CHECK(alGenBuffers((ALuint) 1, &buff));
    return buff;
}

/**
 * generate new source
 * @return created source
 */
ALuint AudioManager::generateSource() {
    ALuint src;
    AL_CHECK(alGenSources((ALuint) 1, &src));
    return src;
}

/**
 * create new buffer, and register it in AL system
 * and add it to freeBuffer and buffers
 */
void AudioManager::createBuffer() {
    _bufferMutex.lock();
    ALuint newBuff = generateBuffer();
    this->buffers.insert(newBuff);
    this->freeBuffers.push_back(newBuff);
    _bufferMutex.unlock();
}

/**
 * create new source, and register it in AL system
 * and add it to freeSource and sources
 */
void AudioManager::createSource() {
    _sourceMutex.lock();
    ALuint newSrc = generateSource();
    this->sources.insert(newSrc);
    this->freeSources.push_back(newSrc);
    _sourceMutex.unlock();
}

/**
 * return free buffer, if can, or create new buffer, and return it
 * @return free buffer
 */
ALuint AudioManager::getFreeBuffer() {
    _bufferMutex.lock();
    if (freeBuffers.size() == 0) {
        createBuffer();
    }
    ALuint freeBuff = freeBuffers[0];
    freeBuffers.erase(freeBuffers.begin());
    _bufferMutex.unlock();
    cout << "return free buffer <" << freeBuff << ">" << endl;
    return freeBuff;
}

/**
 * return free source, if can, or create ew source, and return it
 * @return free source
 */
ALuint AudioManager::getFreeSource() {
    _sourceMutex.lock();
    if (freeSources.size() == 0) {
        createSource();
    }
    ALuint freeSrc = freeSources.at(0);
    freeSources.erase(freeSources.begin());
    _sourceMutex.unlock();
    cout << "return free source <" << freeSrc << ">" << endl;
    return freeSrc;
}

/**
 * clear buffer and replace it refID by new generated buffer
 * @param buffer id of buffer
 */
void AudioManager::clearBuffer(ALuint buffer) {
    if (buffer > 0) {
        _bufferMutex.lock();
//        AL_CHECK(alDeleteBuffers(1, &buffer));
//        buffers.erase(buffer);
        freeBuffers.push_back(buffer);
//        createBuffer();
        _bufferMutex.unlock();
    }
}

/**
 * clear source and replace it refID by new generated source
 * @param source id of source to clear
 */
void AudioManager::clearSource(ALuint source) {
    if (source > 0) {
        _sourceMutex.lock();
        AL_CHECK(alDeleteSources(1, &source));
        sources.erase(source);
        createBuffer();
        _sourceMutex.unlock();
    }
}


void AudioManager::print(const set<ALuint> buffer) {
    for (auto it = buffer.begin(); it != buffer.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}


void AudioManager::print(const vector<ALuint> buffer) {
    for (auto it = buffer.begin(); it != buffer.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}


void AudioManager::print(const std::vector<std::string> vec) {
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}
