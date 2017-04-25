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

    float *createBars(float *frequenceBuffer, int output_buffer);

    void exec(double *input_buffer, size_t input_size);

public:
    void normalize();

    float *getSpectrums() const;

    float *getSpecrtums() const;

    int getLength() const;

    Spectrum(const void *data, size_t offset, size_t chunkLength, int elementInSpectrum, size_t inputDataLength,
             int channel,
             int bits);

    string toString();
};


#endif //ORCHESTRIX_SPECTRUM_H
