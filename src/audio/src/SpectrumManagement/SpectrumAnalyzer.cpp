//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <AudioManagement/OpenAL.h>

using namespace std;

SpectrumAnalyzer::SpectrumAnalyzer(AudioData *data, size_t chunks, int bars) {
    if (data) {
        /**x
         * copy references
         */
        this->rawBytes = data->get_source();
        this->samples = data->get_samples();
        this->bitsPerSample = data->get_bitsPerSample();
        this->channels = data->get_channels();
        this->frequency = data->get_sampleRate();
        this->bars = bars;
        this->elementsInChunk = chunks;
        this->timeBound = this->frequency / (float) this->elementsInChunk;
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
    int countOfSpectrums = this->samples / (elementsInChunk*channels) + 1;

    size_t offsetStep=elementsInChunk*channels;
    for (size_t offset = 0, i = 0; i < countOfSpectrums; i++, offset += offsetStep) {
//        offset=1000000;
        spectrums.push_back(new Spectrum(rawBytes, offset, elementsInChunk, bars, samples,
                                         channels, bitsPerSample));
    }
}