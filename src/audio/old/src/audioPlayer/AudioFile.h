//
// Created by zulus on 13.04.17.
//

#ifndef ORCHESTRIX_AUDIOFILE_H
#define ORCHESTRIX_AUDIOFILE_H

#include <bits/types.h>
#include <string>

typedef struct {
    __int8_t riffStr[4];        //"RIFF" string
    __int32_t fileSize;         // overall size of file in bytes
    __int8_t formatStr[4];      // "WAVE" string
    __int8_t fmpStr[4];         // fmt string with trailing null char
    __int32_t chunkSize;        // length of the format data
    __int16_t audioFormat;      // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    __int16_t numChannels;      // number of channels
    __int32_t sampleRate;       // sampling rate (blocks per second)
    __int32_t byteRate;         // SampleRate * NumChannels * BitsPerSample/8
    __int16_t bytePerSample;    // NumChannels * BitsPerSample/8
    __int16_t bitsPerSample;    // bits per sample, 8- 8bits, 16- 16 bits etc
} Wavheader;

class AudioFile {
    using namespace std;
private:
    Wavheader header;
    __int32_t countOfBytes;
    __int16_t * audioDatai;
    __int32_t sampleCount;
    double *audioDatad;

public:

};


#endif //ORCHESTRIX_AUDIOFILE_H
