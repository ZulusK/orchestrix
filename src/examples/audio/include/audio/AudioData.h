#ifndef ORCHESTRIX_AUDIOSOURCE_H
#define ORCHESTRIX_AUDIOSOURCE_H

#include <bits/types.h>
#include <sndfile.hh>
#include <string>
#include <AL/al.h>

class AudioData {

private:
    ALvoid *_source;              // source of audio data
    ALsizei _size;               // count of bytes in rawBytes
    ALint _sampleRate;          // sampling rate (blocks per second)
    int _channels;              //channel of audio
    int _bitsPerSample;         // bits per sample, 8- 8bits, 16- 16 bits etc
    std::string _name;
    ALsizei _samples;             //count of _samples

private:
    AudioData(const std::string &name, ALvoid *source, ALsizei size, size_t sampleRate, int channels,
              int _bitPerSample);

    static AudioData *load_wav(const std::string &filename);

    static AudioData *load_mp3(const std::string &filename);

    static AudioData *load_ogg(const std::string &filename);

public:
    virtual ~AudioData();

    ALsizei get_samples() const;

    static AudioData *load(const std::string &filename);

    ALvoid *get_source() const;

    ALsizei get_size() const;

    ALint get_sampleRate() const;

    int get_channels() const;

    int get_bitsPerSample() const;

    const std::string &get_name() const;

    std::string toString();

};

#endif //ORCHESTRIX_AUDIOSOURCE_H
