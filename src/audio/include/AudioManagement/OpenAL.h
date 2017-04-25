#ifndef OPEN_AL_H
#define OPEN_AL_H

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

#define AL_CHECK(stmt) do { \
            stmt; \
            CheckOpenALError(#stmt, __LINE__); \
        } while (0);


using namespace std;

void CheckOpenALError(const char *stmt, const char *fname, int line);

string GetOpenALErrorString(int errID);

inline string GetOpenALErrorString(int errID) {
    if (errID == AL_NO_ERROR) {
        return "";
    }
    if (errID == AL_INVALID_NAME) {
        return "Invalid name";
    } else if (errID == AL_INVALID_ENUM) {
        return " Invalid enum ";
    } else if (errID == AL_INVALID_VALUE) {
        return " Invalid value ";
    } else if (errID == AL_INVALID_OPERATION) {
        return " Invalid operation ";
    } else if (errID == AL_OUT_OF_MEMORY) {
        return " Out of memory like! ";
    }
    return " Don't know ";
}

inline void CheckOpenALError(const char *stmt, int line) {
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cout << "OpenAL error " << err << " <" << GetOpenALErrorString(err) << " >";
        std::cout << "at " << line << "with " << string(stmt);
        abort();
    }
};


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

#define BUFFER_SIZE 524288
//#define BUFFER_SIZE 100000
enum {
    MIN_BUFFER_COUNT = 8,
    MIN_SOURCE_COUNT = 4,
    MAX_BUFFER_COUNT = 512,
    MAX_SOURCE_COUNT = 16,
    MAX_BUFFER_PER_PLAYER = 5

};

#endif