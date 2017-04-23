//
// Created by zulus on 13.04.17.
//

#include "AudioManagement/AudioManager.h"
#include <cstring>

using namespace std;

enum {
    MIN_BUFFER_COUNT = 24,
    MIN_SOURCE_COUNT = 4,
    MAX_BUFFER_COUNT = 512,
    MAX_SOURCE_COUNT = 16,
    MAX_BUFFER_PER_PLAYER = 5
};

void print(const vector<string> &vec) {
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}


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
    ALCdevice *deviceAL = alcOpenDevice(NULL);
    if (!deviceAL) {
        cout << "Failed to init OpenAL device." << endl;
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
        AudioBuffer buffer;
        createBuffer(buffer);
    }
    //create sources
    for (int i = 0; i < sourceCnt; i++) {
        AudioSource source;
        createSource(source);
    }
}

/**
 * create new buffer, and register it in AL system
 * and add it to freeBuffer and buffers
 * @param buffer, which stored riID
 */
void AudioManager::createBuffer(AudioBuffer &buffer) {
    AL_CHECK(alGenBuffers((ALuint) 1, &buffer.refID));
    this->buffers.push_back(buffer);
    this->freeBuffers.push_back(buffer);
}

/**
 * create new source, and register it in AL system
 * and add it to freeSource and sources
 * @param source, which stored riID
 */
void AudioManager::createSource(AudioSource &source) {
    AL_CHECK(alGenSources((ALuint) 1, &source.refID));
    this->sources.push_back(source);
    this->freeSources.push_back(source);
}

void AudioManager::printBuffers() {
    for (auto it = buffers.begin(); it != buffers.end(); it++) {
        cout << "b[" << (*it).refID << "] ";
    }
    cout << endl;
}

void AudioManager::printSources() {
    for (auto it = sources.begin(); it != sources.end(); it++) {
        cout << "s[" << (*it).refID << "] ";
    }
    cout << endl;
}


