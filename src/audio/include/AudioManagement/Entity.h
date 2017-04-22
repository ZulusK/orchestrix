//
// Created by zulus on 22.04.17.
//

#ifndef ORCHESTRIX_AUDIOENTITY_H
#define ORCHESTRIX_AUDIOENTITY_H
#define MAX_BUFFER_COUNT 512
#define MAX_SOURCE_COUNT 16
#define MAX_BUFFER_PER_PLAYER 4
#define PRELOAD_BUFFER 3
//#define _DEBUG

typedef struct {
    ALuint refID;
} SoundBuffer;

typedef struct {
    float x;
    float y;
    float z;
} vector3f;
typedef struct {
    ALuint refID;
    SoundBuffer **buffers;
    size_t buffersCount;
} SoundSource;

const std::string GetOpenALErrorString(int errID);

void LogError(const std::string &errorStr);

void CheckOpenALError();

#endif //ORCHESTRIX_AUDIOENTITY_H
