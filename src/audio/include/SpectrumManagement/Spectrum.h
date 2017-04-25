//
// Created by zulus on 25.04.17.
//

#ifndef ORCHESTRIX_SPECTRUM_H
#define ORCHESTRIX_SPECTRUM_H

#include <cstddef>
#include <AudioManagement/OpenAL.h>

class Spectrum {

    float *spectrums;
    float max;
    float min;
    int length;
public:
    void normalize();

    float *getSpecrtums() const;

    float getMax() const;

    float getMin() const;

    int getLength() const;

    void exec(const void *input_buffer, size_t input_size, size_t i, size_t i1, int i2, int i3);
    Spectrum(const void *data, size_t offset, size_t chunkLength, int elementInSpectrum, size_t inputDataLength, int channel,
             int bits);

};


#endif //ORCHESTRIX_SPECTRUM_H
