//
// Created by zulus on 25.04.17.
//

#ifndef ORCHESTRIX_SPECTRUM_H
#define ORCHESTRIX_SPECTRUM_H

#include <cstddef>
#include <AudioManagement/OpenAL.h>

class Spectrum {
    float *specrtums;
    float max;
    float min;
    int length;
public:
    void normalize();

    float *getSpecrtums() const;

    float getMax() const;

    float getMin() const;

    int getLength() const;

    Spectrum(const void *data, size_t offset, size_t chunk, const AudioInfo &info);

    void exec(double *input_buffer, size_t input_size);
};


#endif //ORCHESTRIX_SPECTRUM_H
