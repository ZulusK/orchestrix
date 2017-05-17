//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <AudioManagement/OpenAL.h>
#include <cmath>

using namespace std;

void SpectrumAnalyzer::printError() {
    switch (BASS_ErrorGetCode()) {
        case BASS_ERROR_HANDLE    :
            cout << "handle is not a valid sample handle.." << endl;
            break;
        case BASS_ERROR_NOCHAN    :
            cout
                    << "The sample has no free channels... the maximum number of simultaneous playbacks has been reached, and no BASS_SAMPLE_OVER flag was specified for the sample or onlynew = TRUE."
                    << endl;
            break;
        case BASS_ERROR_TIMEOUT:
            cout
                    << "The sample's minimum playingTime gap (BASS_SAMPLE) has not yet passed since the last channel was created."
                    << endl;
            break;
        case BASS_ERROR_INIT    :
            cout << "BASS_Init has not been successfully called." << endl;
            break;
        case BASS_ERROR_NOTAVAIL    :
            cout << "Sample functions are not available when using the no sound" << endl;
            break;
        case BASS_ERROR_ILLPARAM    :
            cout << "max and/or length is invalid. The length must be specified when loading from memory." << endl;
            break;
        case BASS_ERROR_FILEOPEN    :
            cout << "The file could not be opened." << endl;
            break;
        case BASS_ERROR_FILEFORM    :
            cout << "The file's format is not recognised/supported." << endl;
            break;
        case BASS_ERROR_CODEC    :
            cout <<
                 "The file uses a codec that is not available/supported. This can apply to WAV and AIFF files, and also MP3 files when using the free BASS version."
                 << endl;
            break;
        case BASS_ERROR_FORMAT    :
            cout
                    << "The sample format is not supported by the device/drivers. If the sample is more than stereo or the BASS_SAMPLE_FLOAT flag is used, it could be that they are not supported."
                    << endl;
            break;
        case BASS_ERROR_MEM    :
            cout << "There is insufficient memory." << endl;
            break;
        case BASS_ERROR_NO3D    :
            cout << "Could not initialize 3D support." << endl;
            break;
        case BASS_ERROR_UNKNOWN:
            cout << "Some other mystery problem" << endl;
            break;
        case BASS_ERROR_ENDED    :
            cout << "The channel has reached the end." << endl;
            break;
        case BASS_ERROR_BUFLOST    :
            cout << "Should not happen... check that a valid window handle was used with BASS_Init." << endl;
            break;
    }
}

SpectrumAnalyzer::SpectrumAnalyzer(AudioData *data, int mode, int bars) {
    if (data) {
        /**
         * copy references
         */
        this->rawBytes = data->get_source();
        this->samples = data->get_size();
        this->bitsPerSample = data->get_bitsPerSample();
        this->channels = data->get_channels();
        this->frequency = data->get_sampleRate();
        this->bars = bars;


        switch (mode) {
            case SAMPLE_1024:
                this->elementsInChunk = 2048;
                this->mode = BASS_DATA_FFT2048;
                break;
            case SAMPLE_2048:
                this->elementsInChunk = 4096;
                this->mode = BASS_DATA_FFT4096;
                break;
            case SAMPLE_4096:
                this->elementsInChunk = 8192;
                this->mode = BASS_DATA_FFT8192;
                break;
            case SAMPLE_8192:
                this->elementsInChunk = 16384;
                this->mode = BASS_DATA_FFT16384;
                break;
            default:
                this->elementsInChunk = 1024;
                this->mode = BASS_DATA_FFT1024;
                break;
        }
        this->timeBound = (float) (this->elementsInChunk) / (float) this->frequency / data->get_channels();

        exec(data->get_name());
    } else throw "Null pointer to data";
}

void SpectrumAnalyzer::exec(string filename) {
    int countOfSpectrums = this->samples / (elementsInChunk * channels) + 1;
    if (!BASS_Init(-1, frequency, 0, NULL, NULL)) {
        cout << "Can't initialize device" << endl;
        return;
    }
    HSAMPLE hsample = BASS_SampleLoad(FALSE, filename.c_str(), 0, 0, 1, 0);
    printError();
    HCHANNEL hchannel = BASS_SampleGetChannel(hsample, FALSE);
    printError();
    for (size_t i = 0; i < countOfSpectrums; i++) {
        Spectrum *s = new Spectrum(hchannel, timeBound * i, mode, bars);
        spectrums.push_back(s);
    }
    BASS_SampleFree(hchannel);
    BASS_Free();
    this->count = spectrums.size();
    findShoot();
}

void SpectrumAnalyzer::findShoot() {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += getAverageEnergy(i);
    }
    this->SHOOT = sum / count * sqrt(40);
    if (this->SHOOT >= 1) {
        this->SHOOT = 0.9;
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

SpectrumAnalyzer::~SpectrumAnalyzer() {
    for (int i = 0; i < spectrums.size(); i++) {
        delete spectrums[i];
    }
    spectrums.clear();
}

float SpectrumAnalyzer::getAverageEnergy(int ind) {
    if (ind < 0 || ind >= this->spectrums.size()) {
        return 1.e-10;
    }
    float average = 0;
    int count = 0;
    for (int i = -3; i < 3; i++) {
        int id = i + ind;
        if (i != 0 && id >= 0 && id < spectrums.size()) {
            average += spectrums[id]->getEnergy();
            count++;
        }
    }
    average /= count;
    return average;
}

bool SpectrumAnalyzer::isShoot(int ind) {
    if (ind < 0 || ind >= this->spectrums.size()) {
        return false;
    }
    return (getAverageEnergy(ind) / spectrums[ind]->getEnergy() < this->SHOOT);
}

float SpectrumAnalyzer::getSHOOT() const {
    return SHOOT;
}

unsigned long SpectrumAnalyzer::getCount() const {
    return count;
}
