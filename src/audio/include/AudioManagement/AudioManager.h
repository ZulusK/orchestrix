#ifndef ORCHESTRIX_AUDIOPMANAGER_H
#define ORCHESTRIX_AUDIOPMANAGER_H


#include "AudioData.h"
#include "AudioPlayer.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <Entity.h>

class AudioManager {
private:
    AudioData *sound;
    ALCdevice *device;
    ALCcontext *context;
    std::vector<SoundBuffer *> buffers;
    std::vector<SoundSource *> sources;
    std::vector<SoundBuffer *> freeBuffers;
    std::vector<SoundSource *> freeSources;

    vector3f lispos;
    vector3f lisvel;
    ALfloat *listenerOri;

    AudioManager(ALCdevice *device, ALCcontext *contex, int source, int buffer);

public:
    static AudioManager *init(int source, int buffer);

    virtual ~AudioManager();

    AudioPlayer *getAudioPlayer(AudioData *data, int reservedBuffersCount = 3);

    void play(AudioPlayer *player);

    void deletePlayer(AudioPlayer *player);
};


#endif //ORCHESTRIX_AUDIOPLAYER_H
