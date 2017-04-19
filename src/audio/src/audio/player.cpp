//
// Created by zulus on 04.04.17.
//

#include <sndfile.hh>
#include <AL/al.h>
#include <AL/alc.h>
#include <cstring>
#include <playerWav.h>

using namespace std;

static void list_audio_devices(const ALCchar *devices) {
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;
//
//    fprintf(stdout, "Devices list:\n");
//    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0') {
//        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
//    fprintf(stdout, "----------\n");
}

void Player_free(Player *player) {
    if (player != NULL) {
        if (player->device != NULL) {
            alcCloseDevice(player->device);
        }
        if (player->context != NULL) {
            alcMakeContextCurrent(NULL);
            alcDestroyContext(player->context);
        }

        alDeleteSources(1, &player->source);

        alDeleteBuffers(1, &player->buffer);

        free(player);
    }
}


void Player_play(Player *player) {
    alcMakeContextCurrent(player->context);
    alSourcePlay(player->source);
    ALint source_state;
// check for errors
    alGetSourcei(player->source, AL_SOURCE_STATE, &source_state);
// check for errors
    while (source_state == AL_PLAYING) {
        alGetSourcei(player->source, AL_SOURCE_STATE, &source_state);

    }
}

Player *Player_create(void *audioData, __int32_t count, int channels, __int32_t freqWav, int depth) {
    Player *player = (Player *) malloc(sizeof(Player));
    if (player == NULL) {
        return NULL;
    }
    player->device = NULL;
    player->context = NULL;
    player->source = 0;
    player->buffer = 0;

    player->device = alcOpenDevice(NULL);
    if (!player->device) {
        Player_free(player);
        return NULL;
    }
    ALboolean enumeration;
    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
        printf("Enum not supported\n");
    else {
        printf("Enum supported\n");
        Player_free(player);
        return NULL;
    }

    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

    ALCenum error;
    error = alGetError();
    if (error != AL_NO_ERROR) {
        printf("sm is wrong, error detected\n");
        Player_free(player);
        return NULL;
    }


    player->context = alcCreateContext(player->device, NULL);

    if (!alcMakeContextCurrent(player->context)) {
        printf("Failed to create contex\n");
        Player_free(player);
        return NULL;
    }

    ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0, 0, 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);


    alGenSources((ALuint) 1, &player->source);
    alSourcef(player->source, AL_PITCH, 1);
    alSourcef(player->source, AL_GAIN, 1);
    alSource3f(player->source, AL_POSITION, 0, 0, 0);
    alSource3f(player->source, AL_VELOCITY, 0, 0, 0);
    alSourcei(player->source, AL_LOOPING, AL_FALSE);

    alGenBuffers((ALuint) 1, &player->buffer);

    player->size = count;
    player->freq = freqWav;
    player->format = AL_FORMAT_STEREO16;
    ALvoid *data = audioData;
    player->loop = AL_FALSE;

    if (depth == 16) {
        if (channels == 2) {
            player->format = AL_FORMAT_STEREO16;
        } else {
            player->format = AL_FORMAT_MONO16;
        }
    } else if (depth == 8) {
        if (channels == 2) {
            player->format = AL_FORMAT_STEREO8;
        } else {
            player->format = AL_FORMAT_MONO8;
        }
    } else {
        Player_free(player);
        return NULL;
    }
    alBufferData(player->buffer, player->format, data, player->size, player->freq);
    alSourcei(player->source, AL_BUFFER, player->buffer);
    return player;
}
