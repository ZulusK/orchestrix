//
// Created by zulus on 28.03.17.
//

#ifndef ORCHESTRIX_WAVE_H
#define ORCHESTRIX_WAVE_H

#include <stdlib.h>

// WAVE file header format
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

typedef struct {
    Wavheader header;
    __int16_t *datai;
    double *datad;
    long samples;

} WavFile;

WavFile *WavFile_read(char *filename);

void WavFile_print(WavFile *wav);

void readWavFilei(const char *fname, WavFile *wav);

void WavFile_free(WavFile *wav);

#endif //ORCHESTRIX_WAVE_H
