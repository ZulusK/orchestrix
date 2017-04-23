#ifndef OPEN_AL_H
#define OPEN_AL_H

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>

#ifndef AL_CHECK
#ifdef _DEBUG
#define AL_CHECK(stmt) do { \
            stmt; \
            CheckOpenALError(#stmt, __FILE__, __LINE__); \
        } while (0);
#else
#define AL_CHECK(stmt) stmt
#endif
#endif


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

inline void CheckOpenALError(const char *stmt, const char *fname, int line) {

    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        std::cout << "OpenAL error " << err << " <" << GetOpenALErrorString(err) << " >";
        std::cout << "at " << string(fname) << ":" << line << "with " << string(stmt);
        //abort();
    }
};

typedef struct {
    float x;
    float y;
    float z;
} vector3f;

/**
   * store id of buffer
   */
typedef struct {
    ALuint refID;
} AudioBuffer;
/**
 * store id of source
 */
typedef struct {
    ALuint refID;
} AudioSource;

typedef struct {
    ALenum state;
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

enum {
    MIN_BUFFER_COUNT = 24,
    MIN_SOURCE_COUNT = 4,
    MAX_BUFFER_COUNT = 512,
    MAX_SOURCE_COUNT = 16,
    MAX_BUFFER_PER_PLAYER = 5
};

#endif