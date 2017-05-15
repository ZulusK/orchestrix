//
// Created by zulus on 25.04.17.
//

#ifndef ORCHESTRIX_SPECTRUMANALYZER_H
#define ORCHESTRIX_SPECTRUMANALYZER_H

#include <vector>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioPlayer.h>
#include <SpectrumManagement/Spectrum.h>

class SpectrumAnalyzer {
private:
    vector<Spectrum *> spectrums;
    size_t bars;

    unsigned int mode;
    size_t elementsInChunk;
    float timeBound;
    void *rawBytes;
    size_t samples;
    int channels;
    int frequency;
    int bitsPerSample;

    void exec(string filename);

public:
    SpectrumAnalyzer(AudioData *data, int mode, int bars);
    ~SpectrumAnalyzer();
    const vector<Spectrum *> &getSpectrums() const;

    size_t getBars() const;

    size_t getElementsInChunk() const;

    float getTimeBound() const;

    void *getRawBytes() const;

    size_t getSamples() const;

    int getChannels() const;

    int getFrequency() const;

    int getBitsPerSample() const;

    static void printError();
};


#endif //ORCHESTRIX_SPECTRUMANALYZER_H
