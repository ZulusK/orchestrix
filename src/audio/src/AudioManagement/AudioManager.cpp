//
// Created by zulus on 13.04.17.
//

#include "AudioManagement/AudioManager.h"
#include <iostream>
#include <AudioManagement/AudioManager.h>
#include <AudioManagement/Entity.h>
#include <cstring>

#ifndef AL_CHECK
#ifdef _DEBUG
#define AL_CHECK(stmt) do { \
            stmt; \
            CheckOpenALError(); \
        } while (0);
#else
#define AL_CHECK(stmt) stmt
#endif
#endif

using namespace std;

/*
 * check for an OpenAL errors
 */
const string GetOpenALErrorString(int errID) {
    if (errID == AL_NO_ERROR) return "";
    if (errID == AL_INVALID_NAME) return "Invalid name";
    if (errID == AL_INVALID_ENUM) return " Invalid enum ";
    if (errID == AL_INVALID_VALUE) return " Invalid value ";
    if (errID == AL_INVALID_OPERATION) return " Invalid operation ";
    if (errID == AL_OUT_OF_MEMORY) return " Out of memory like! ";
    return " Don't know ";
}

void LogError(const string &errorStr) {
    cout << "Catch error <" << errorStr << ">" << endl;
}

void list_audio_devices(const ALCchar *devices) {
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;

    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0') {
        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
}

void CheckOpenALError() {
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        LogError("OpenAL error " + GetOpenALErrorString(err));
    }
};

AudioManager *AudioManager::init(int source, int buffer) {
    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    if (source < 0 || source > MAX_SOURCE_COUNT) {
        source = MAX_SOURCE_COUNT;
    }
    if (buffer < 0 || buffer > MAX_BUFFER_COUNT) {
        buffer = MAX_BUFFER_COUNT;
    }
    ALCdevice *deviceAL = alcOpenDevice(NULL);
    if (!deviceAL) {
        LogError("Failed to init OpenAL device.");
    }
    ALCcontext *contextAL = alcCreateContext(deviceAL, NULL);
    AL_CHECK(alcMakeContextCurrent(contextAL));
    return new AudioManager(deviceAL, contextAL, source, buffer);
}

AudioManager::AudioManager(ALCdevice *device, ALCcontext *contex, int sourceCnt, int bufferCnt) {
    this->device = device;
    this->context = contex;
    //
    this->lisvel.x = 0;
    this->lisvel.y = 0;
    this->lisvel.z = 0;
    //
    this->lispos.x = 0;
    this->lispos.y = 0;
    this->lispos.z = 1;
    //
    this->listenerOri = new ALfloat[6];

    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 1.0;
    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 0.0;
    this->listenerOri[0] = 1.0;
    //create buffers
    for (int i = 0; i < bufferCnt; i++) {
        SoundBuffer *buffer = new SoundBuffer();
        AL_CHECK(alGenBuffers((ALuint) 1, &buffer->refID));
        this->buffers.push_back(buffer);
    }
    //create sources
    for (int i = 0; i < sourceCnt; i++) {
        SoundSource *source = new SoundSource();
        AL_CHECK(alGenSources((ALuint) 1, &source->refID));
        this->sources.push_back(source);
    }
    //create free buffers
    for (int i = 0; i < this->buffers.size(); i++) {
        this->freeBuffers.push_back(this->buffers[i]);
    }
    //create free sources
    for (int i = 0; i < this->sources.size(); i++) {
        this->freeSources.push_back(this->sources[i]);
    }
}

AudioPlayer *AudioManager::getAudioPlayer(AudioData *data, int reservedBuffersCount) {
    AudioPlayer *player = NULL;
    if (data && freeSources.size() > 0 && freeBuffers.size() > 0) {
        //reserve available source
        SoundSource *reserveSource = freeSources[0];
        freeSources.erase(freeSources.begin());
        //check, is reserved buffers count is valid
        if (reservedBuffersCount < 0 || reservedBuffersCount > freeBuffers.size() ||
            reservedBuffersCount > MAX_BUFFER_PER_PLAYER) {
            reserveSource->buffersCount = (MAX_BUFFER_PER_PLAYER > freeBuffers.size()) ? freeBuffers.size()
                                                                                       : MAX_BUFFER_PER_PLAYER;
        } else {
            reserveSource->buffersCount = reservedBuffersCount;
        }
        //reserve buffers
        reserveSource->buffers = new SoundBuffer *[reserveSource->buffersCount];
        for (int i = 0; i < reservedBuffersCount; i++) {
            reserveSource->buffers[i] = freeBuffers[0];
            freeBuffers.erase(freeBuffers.begin());
        }
        player = new AudioPlayer(data, reserveSource);
    }
    return player;
}

void AudioManager::play(AudioPlayer *player) {
    if (player) {
        alcMakeContextCurrent(context);
        // check for errros
        alListener3f(AL_POSITION, lispos.x, lispos.y, lispos.z);
// check for errors
        alListener3f(AL_VELOCITY, lisvel.x, lisvel.y, lisvel.z);
// check for errors
        alListenerfv(AL_ORIENTATION, listenerOri);

        player->play();
    }
}

void AudioManager::deletePlayer(AudioPlayer *player) {
    //todo
}

AudioManager::~AudioManager() {
// cleanup context
    for (auto itB = buffers.begin(); itB != buffers.end(); itB++) {
        alDeleteBuffers(1, &(*itB)->refID);
        delete (*itB);
    }
    buffers.clear();

    for (auto itS = sources.begin(); itS != sources.end(); itS++) {
        alDeleteSources(1, &(*itS)->refID);
        delete (*itS);
    }
    buffers.clear();

    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
