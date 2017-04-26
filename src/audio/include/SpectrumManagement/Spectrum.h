//
// Created by zulus on 25.04.17.
//

#ifndef ORCHESTRIX_SPECTRUM_H
#define ORCHESTRIX_SPECTRUM_H

#include <cstddef>
#include <AudioManagement/OpenAL.h>

class Spectrum {

    float *spectrums;
    int length;

    float *createBars(float *frequenceBuffer, int size);

    void exec(double *input_buffer, size_t input_size);

    void fillBuffer(const __int16_t *A, double *B, size_t lenA, size_t lenB, int channel);

    void fillBuffer(const __int8_t *A, double *B, size_t lenA, size_t lenB, int channel);

public:
    void normalize();

    float *getSpectrums() const;

    int getLength() const;

    Spectrum(const void *data, size_t offset, size_t chunkLength, int elementInSpectrum, size_t inputDataLength,
             int channel,
             int bits);

    string toString();
};


#endif //ORCHESTRIX_SPECTRUM_H
