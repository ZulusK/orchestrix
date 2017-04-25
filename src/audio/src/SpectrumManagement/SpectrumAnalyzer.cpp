//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <AudioManagement/OpenAL.h>

using namespace std;

SpectrumAnalyzer::SpectrumAnalyzer(AudioData *data, size_t elementsInSpctrum) {
    if (data) {
        /**
         * copy references
         */
        this->rawBytes = data->get_source();
        this->info.samples = data->get_size();
        this->info.format = toALformat(data->get_channels(), data->get_bitsPerSample());
        this->info.frequency = data->get_sampleRate();
        this->elementsInSpectrum = elementsInSpctrum;
        this->timeBound = info.frequency / (float) this->elementsInSpectrum;
        /**
         * process spectrums
         */
        exec();
    } else throw "Null pointer to data";
}

/**
 * calculate spectrums to source
 */
void SpectrumAnalyzer::exec() {
    int countOfSpectrums = info.samples / elementsInSpectrum + 1;


    for (size_t offset = 0, i = 0; i < countOfSpectrums; i++, offset += elementsInSpectrum) {
        spectrums.push_back(new Spectrum(rawBytes, offset, elementsInSpectrum, info));
    }
}