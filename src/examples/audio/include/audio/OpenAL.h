#ifndef OPEN_AL_H
#define OPEN_AL_H

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

#ifdef _DEBUG
#define AL_CHECK(stmt) do { \
            stmt; \
            CheckOpenALError(#stmt, __LINE__); \
        } while (0);
#else
#define AL_CHECK(stmt) do {\
            stmt;\
        }while(0);
#endif


std::string GetOpenALErrorString(int errID);


typedef struct {
    float x;
    float y;
    float z;
} vector3f;

typedef struct {
    ALenum format;
    ALsizei samples;
    ALint frequency;
} AudioInfo;
typedef struct {
    vector3f pos;
    vector3f vel;
    float pitch;
    float gain;
} PlayerInfo;

void CheckOpenALError();

std::string GetOpenALErrorString(int errID);

void CheckOpenALError(const char *stmt, int line);

/**
 * convert not Al-format data to ALenum
 * @param channels count of channels
 * @param bitsPerSample bitser sample (eq. 16 or 8)
 * @return ALenum for presentetive foram
 */
inline ALenum toALformat(int channels, int bitsPerSample) {
    if (channels == 2) {
        if (bitsPerSample == 16) {
            return AL_FORMAT_STEREO16;
        } else if (bitsPerSample == 8) {
            return AL_FORMAT_STEREO8;
        }
    } else if (channels == 1) {
        if (bitsPerSample == 16) {
            return AL_FORMAT_MONO16;
        } else if (bitsPerSample == 8) {
            return AL_FORMAT_MONO8;
        }
    }
    return AL_ILLEGAL_ENUM;
}

#define BUFFER_SIZE 524288
enum {
    MIN_BUFFER_COUNT = 8,
    MIN_SOURCE_COUNT = 4,
    MAX_BUFFER_COUNT = 512,
    MAX_SOURCE_COUNT = 16,
    MAX_BUFFER_PER_PLAYER = 5
};

#endif