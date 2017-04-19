//
// Created by zulus on 04.04.17.
//

#ifndef TESTPROJ_PLAYERWAV_H
#define TESTPROJ_PLAYERWAV_H

#include <bits/types.h>
#include <AL/al.h>
#include <AL/alc.h>

typedef struct {
    ALCdevice *device;
    ALCcontext *context;
    ALuint source;
    ALuint buffer;
    ALsizei size;
    ALsizei freq;
    ALenum format;
    ALboolean loop;

} Player;

void Player_play(Player *player);

void Player_free(Player *player);

Player *Player_create(void *audioData, __int32_t count, int channels, __int32_t freqWav, int depth);

#endif //TESTPROJ_PLAYERWAV_H
