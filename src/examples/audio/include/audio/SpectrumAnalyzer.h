#ifndef ORCHESTRIX_SPECTRUMANALYZER_H
#define ORCHESTRIX_SPECTRUMANALYZER_H

#include <vector>
#include <audio/AudioData.h>
#include <audio/AudioPlayer.h>
#include <audio/Spectrum.h>

class SpectrumAnalyzer {
private:
    vector<Spectrum *> spectrums;
    size_t bars;
    float SHOOT;
    unsigned int mode;
    size_t elementsInChunk;
    float timeBound;
    void *rawBytes;
    size_t samples;
    int channels;
    int frequency;
    int bitsPerSample;
    unsigned long count;

    void exec(string filename);

    void findShoot();

    float getAverageEnergy(int ind);

public:
    static void printError();

    float getSHOOT() const;

    unsigned long getCount() const;

    SpectrumAnalyzer(AudioData *data, int mode, int bars);

    ~SpectrumAnalyzer();

    const float *  getSpectrums(long ind) const;
    const vector<Spectrum *> &getSpectrums() const;

    size_t getBars() const;

    size_t getElementsInChunk() const;

    float getTimeBound() const;

    void *getRawBytes() const;

    size_t getSamples() const;

    int getChannels() const;

    int getFrequency() const;

    int getBitsPerSample() const;

    bool isShoot(int ind);
};


#endif //ORCHESTRIX_SPECTRUMANALYZER_H
