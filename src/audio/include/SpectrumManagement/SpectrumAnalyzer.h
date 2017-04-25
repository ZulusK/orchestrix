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
    size_t elementsInSpectrum;
    float timeBound;
    void *rawBytes;
    AudioInfo info;
public:
    SpectrumAnalyzer(AudioData *data, size_t elementsInSpectrum);
    void exec();
};


#endif //ORCHESTRIX_SPECTRUMANALYZER_H
