#ifndef ORCHESTRIX_AUDIOPMANAGER_H
#define ORCHESTRIX_AUDIOPMANAGER_H

#include <AL/alc.h>
#include <AL/al.h>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/OpenAL.h>
#include <map>
#include <vector>

class AudioManager {
private:
    AudioData *sound;
    ALCdevice *device;
    ALCcontext *context;
    float masterVolume;

    vector3f listenerVel;
    vector3f listenerPos;
    float listenerOri[6];

    std::vector<AudioBuffer *> buffers;
    std::vector<AudioSource *> sources;
    std::vector<AudioBuffer *> freeBuffers;
    std::vector<AudioSource *> freeSources;

    AudioManager(ALCdevice *device, ALCcontext *contex, int source, int buffer);

    void destroyBuffer(AudioBuffer *buffer);

    void destroySource(AudioSource *source);

public:
    static AudioManager *init(int source = 8, int buffer = 64);

    virtual ~AudioManager();

    static vector<string> getAllDevices();

    void printSources();

    void printBuffers();

    AudioBuffer *getFreeBuffer();

    AudioSource *getFreeSource();

    void generateBuffer(AudioBuffer *buffer);

    void generateSource(AudioSource *source);

    void createBuffer(AudioBuffer *buffer);

    void createSource(AudioSource *source);

    void clearBuffer(AudioBuffer *buffer);

    void clearSource(AudioSource *source);
};

#endif //ORCHESTRIX_AUDIOPLAYER_H
