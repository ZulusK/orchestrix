
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <wavFile.h>
#include <stdio.h>
#include <pbconsole.h>
#include <progbase.h>
#include <string.h>
#define FILE_NAME "/home/zulus/Projects/GitProj/orchestrix/res/21pilots.wav"

static void list_audio_devices(const ALCchar *devices) {
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

void play(char *fileName) {

    ALCdevice *device;

    device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "Oops\n");
        return;
    }
    ALboolean enumeration;
    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
        printf("Enum not supported\n");
    else printf("Enum supported\n");
    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

    ALCenum error;

    error = alGetError();
    if (error != AL_NO_ERROR) {
        printf("sm is wrong");
    }

    ALCcontext *context;
    context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context)) {
        printf("Failed to create contex\n");
        return;
    }
    ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0, 0, 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);

    ALuint source;
    alGenSources((ALuint) 1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);

    ALuint buffer;

    alGenBuffers((ALuint) 1, &buffer);
    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;
    alutLoadWAVFile(fileName, &format, &data, &size, &freq, &loop);
    alBufferData(buffer, format, data, size, freq);
    alSourcei(source, AL_BUFFER, buffer);


    alSourcePlay(source);
    ALint source_state;
// check for errors
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
// check for errors
    while (source_state == AL_PLAYING && !conIsKeyDown()) {
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        // check for errors
    }
// cleanup context
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void playWav(Wavfile *wav) {

    ALCdevice *device;

    device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "Oops\n");
        return;
    }
    ALboolean enumeration;
    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
        printf("Enum not supported\n");
    else printf("Enum supported\n");
    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

    ALCenum error;

    error = alGetError();
    if (error != AL_NO_ERROR) {
        printf("sm is wrong");
    }

    ALCcontext *context;
    context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context)) {
        printf("Failed to create contex\n");
        return;
    }

    ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0, 0, 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);

    ALuint source;
    alGenSources((ALuint) 1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    ALuint buffer;
    alGenBuffers((ALuint) 1, &buffer);
    ALsizei size = wav->count;
    ALsizei freq = wav->wavheader.sampleRate;
    ALenum format=AL_FORMAT_MONO16;
    ALvoid *data = wav->data;
    ALboolean loop = AL_FALSE;

    if (wav->depth==2) {
        if (wav->wavheader.numChannels == 2) {
            format = AL_FORMAT_STEREO16;
        } else {
            format = AL_FORMAT_MONO16;
        }
    } else if (wav->depth==1) {
        if (wav->wavheader.numChannels == 2) {
            format = AL_FORMAT_STEREO8;
        } else {
            format = AL_FORMAT_MONO8;
        }
    }else{
        return;
    }
    alBufferData(buffer, format, data, size, freq);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    ALint source_state;
// check for errors
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
// check for errors
    while (source_state == AL_PLAYING) {
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        // check for errors
    }
// cleanup context
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

int main() {

    Wavfile *wav = Wavfile_create(FILE_NAME);
    printf("Read data from %s\n", FILE_NAME);
    Wavfile_toString(wav);
//    play(FILE_NAME);
    playWav(wav);
    FILE * fout=fopen("/home/zulus/Projects/GitProj/orchestrix/res/mus.csv","w");
    for(__int32_t i=0; i<100000;i+=100){
        fprintf(fout,"%i, %i\n",i,((__int16_t *)wav->data)[i]);
    }
    Wavfile_free(&wav);
    return 0;
}