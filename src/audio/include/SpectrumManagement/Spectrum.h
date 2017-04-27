//
// Created by zulus on 25.04.17.
//

#ifndef ORCHESTRIX_SPECTRUM_H
#define ORCHESTRIX_SPECTRUM_H

#include <cstddef>
#include <AudioManagement/OpenAL.h>
#include <bass.h>

enum {
    SAMPLE_8192,
    SAMPLE_4096,
    SAMPLE_2048,
    SAMPLE_1024
};

class Spectrum {

    float *spectrums;
    int length;

    float *createBars(float *frequenceBuffer, int size);

    void exec(double *input_buffer, size_t input_size);

    void fillBuffer(const __int16_t *A, __int16_t *B, size_t lenA, size_t lenB, int channel);

    void fillBuffer(const __int8_t *A, __int8_t *B, size_t lenA, size_t lenB, int channel);

public:
    void normalize();

    float *getSpectrums() const;

    int getLength() const;

    Spectrum(const void *data, size_t offset, size_t chunkLength, int elementInSpectrum, size_t inputDataLength,
             int channel,
             int bits);

    Spectrum(HSTREAM hchannel, double offset, int mode, int bars);
    ~Spectrum();
    string toString();
};


#endif //ORCHESTRIX_SPECTRUM_H
