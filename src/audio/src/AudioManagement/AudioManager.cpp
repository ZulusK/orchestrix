//
// Created by zulus on 13.04.17.
//

#include "AudioManagement/AudioManager.h"
#include <cstring>
#include <AudioManagement/OpenAL.h>

using namespace std;


void print(const vector<string> &vec) {
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

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

AudioManager::~AudioManager() {

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
    cout << "=================================================" << endl;
    cout << "All devices:" << endl;
    print(getAllDevices());
    cout << "=================================================" << endl;
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
        AudioBuffer *buffer = new AudioBuffer;
        createBuffer(buffer);
    }
    //create sources
    for (int i = 0; i < sourceCnt; i++) {
        AudioSource *source = new AudioSource;
        createSource(source);
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
 * @param buffer ref to AudioBuffer to store generated buffer
 */
void AudioManager::generateBuffer(AudioBuffer *buffer) {
    AL_CHECK(alGenBuffers((ALuint) 1, &buffer->refID));
}

/**
 * generate new source
 * @param source ref to AudioSource to store generated source
 */
void AudioManager::generateSource(AudioSource *source) {
    AL_CHECK(alGenSources((ALuint) 1, &source->refID));;
}

/**
 * create new buffer, and register it in AL system
 * and add it to freeBuffer and buffers
 * @param buffer, which stored riID
 */
void AudioManager::createBuffer(AudioBuffer *buffer) {

    if (buffer) {
        _getBuffer.lock();
        generateBuffer(buffer);
        this->buffers.push_back(buffer);
        this->freeBuffers.push_back(buffer);
        _getBuffer.unlock();
    }

}

/**
 * create new source, and register it in AL system
 * and add it to freeSource and sources
 * @param source, which stored riID
 */
void AudioManager::createSource(AudioSource *source) {
    if(source) {
        _getSource.lock();
        generateSource(source);
        this->sources.push_back(source);
        this->freeSources.push_back(source);
        _getSource.unlock();
    }
}

/**
 * print all registered buffers
 */
void AudioManager::printBuffers() {
    for (auto it = buffers.begin(); it != buffers.end(); it++) {
        cout << "b[" << (*it)->refID << "] ";
    }
    cout << endl;
}

/**
 * print all registered buffers
 */
void AudioManager::printFreeBuffers() {
    cout << "free buffers[" << freeBuffers.size() << "]" << endl;
    for (auto it = freeBuffers.begin(); it != freeBuffers.end(); it++) {
        cout << "b[" << (*it)->refID << "] ";
    }
    cout << endl;
}

/**
 * print all registered sources
 */
void AudioManager::printSources() {
    for (auto it = sources.begin(); it != sources.end(); it++) {
        cout << "s[" << (*it)->refID << "] ";
    }
    cout << endl;
}

/**
 * print all registered sources
 */
void AudioManager::printFreeSources() {
    for (auto it = freeSources.begin(); it != freeSources.end(); it++) {
        cout << "s[" << (*it)->refID << "] ";
    }
    cout << endl;
}

/**
 * return free buffer, if can, or create ew buffer, and return it
 * @return free buffer
 */
AudioBuffer *AudioManager::getFreeBuffer() {
    AudioBuffer *freeBuff;
    _getBuffer.lock();
    if (freeBuffers.size() == 0) {
        freeBuff = new AudioBuffer();
        createBuffer(freeBuff);
    }
    freeBuff = freeBuffers[0];
    freeBuffers.erase(freeBuffers.begin());
    _getBuffer.unlock();
    return freeBuff;
}

/**
 * return free source, if can, or create ew source, and return it
 * @return free source
 */
AudioSource *AudioManager::getFreeSource() {
    AudioSource *freeSrc;
    _getSource.lock();
    if (freeSources.size() == 0) {
        freeSrc = new AudioSource();
        createSource(freeSrc);
    }
    printFreeSources();
    freeSrc = freeSources.at(0);
    freeSources.erase(freeSources.begin());
    _getSource.unlock();
    return freeSrc;
}

/**
 * clear buffer and replace it refID by new generated buffer
 * @param buffer
 */
void AudioManager::clearBuffer(AudioBuffer *buffer) {
    if (buffer) {
        AL_CHECK(alDeleteBuffers(1, &buffer->refID));
        generateBuffer(buffer);
        freeBuffers.push_back(buffer);
    }
}

/**
 * clear source and replace it refID by new generated source
 * @param source
 */
void AudioManager::clearSource(AudioSource *source) {
    if (source) {
        AL_CHECK(alDeleteSources(1, &source->refID));
        generateSource(source);
        freeSources.push_back(source);
    }
}