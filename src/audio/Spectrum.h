//
// Created by zulus on 25.04.17.
//

#ifndef ORCHESTRIX_SPECTRUM_H
#define ORCHESTRIX_SPECTRUM_H

#include <cstddef>
#include <audio/OpenAL.h>
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
    float energy;
public:
    float getEnergy() const;

private:
    float *calculateBars(float *fft, int size);

    void execute(HCHANNEL hchannel, double offset, long mode, int bars);

public:

    float *getSpectrums() const;

    int getLength() const;

    Spectrum(HSTREAM hchannel, double offset, long mode, int bars);

    ~Spectrum();

    std::string toString();
};


#endif //ORCHESTRIX_SPECTRUM_H
