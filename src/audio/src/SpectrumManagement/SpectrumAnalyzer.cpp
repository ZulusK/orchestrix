//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <AudioManagement/OpenAL.h>

using namespace std;

SpectrumAnalyzer::SpectrumAnalyzer(AudioData *data, size_t chunks, int bars) {
    if (data) {
        /**
         * copy references
         */
        this->rawBytes = data->get_source();
        this->samples = data->get_samples();
        this->bitsPerSample = data->get_bitsPerSample();
        this->channels = data->get_channels();
        this->frequency = data->get_sampleRate();
        this->bars = bars;
        this->elementsInChunk = chunks;
        this->timeBound = (float) this->elementsInChunk / this->frequency;
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
    int countOfSpectrums = this->samples / (elementsInChunk * channels) + 1;
    size_t offsetStep = elementsInChunk * channels;
    for (size_t offset = 0, i = 0; i < countOfSpectrums; i++, offset += offsetStep) {
        Spectrum *s = new Spectrum(rawBytes, offset, elementsInChunk, bars, samples,
                                   channels, bitsPerSample);
        spectrums.push_back(s);
    }
}

const vector<Spectrum *> &SpectrumAnalyzer::getSpectrums() const {
    return spectrums;
}

size_t SpectrumAnalyzer::getBars() const {
    return bars;
}

size_t SpectrumAnalyzer::getElementsInChunk() const {
    return elementsInChunk;
}

float SpectrumAnalyzer::getTimeBound() const {
    return timeBound;
}

void *SpectrumAnalyzer::getRawBytes() const {
    return rawBytes;
}

size_t SpectrumAnalyzer::getSamples() const {
    return samples;
}

int SpectrumAnalyzer::getChannels() const {
    return channels;
}

int SpectrumAnalyzer::getFrequency() const {
    return frequency;
}

int SpectrumAnalyzer::getBitsPerSample() const {
    return bitsPerSample;
}
