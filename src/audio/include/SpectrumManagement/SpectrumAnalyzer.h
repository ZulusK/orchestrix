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
    size_t elementsInChunk;
    float timeBound;
    void *rawBytes;
    size_t samples;
    int channels;
    int frequency;
    int bitsPerSample;

    void exec();

public:
    SpectrumAnalyzer(AudioData *data, size_t chunks, int bars);

};


#endif //ORCHESTRIX_SPECTRUMANALYZER_H
