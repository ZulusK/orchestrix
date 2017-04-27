//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <AudioManagement/OpenAL.h>

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
            cout << "The sample's minimum time gap (BASS_SAMPLE) has not yet passed since the last channel was created."
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
                this->elementsInChunk = 512;
                this->mode = BASS_DATA_FFT512;
                break;
            case SAMPLE_2048:
                this->elementsInChunk = 1024;
                this->mode = BASS_DATA_FFT1024;
                break;
            case SAMPLE_4096:
                this->elementsInChunk = 2048;
                this->mode = BASS_DATA_FFT2048;
                break;
            case SAMPLE_8192:
                this->elementsInChunk = 4096;
                this->mode = BASS_DATA_FFT4096;
                break;
            default:
                this->elementsInChunk = 512;
                this->mode = BASS_DATA_FFT512;
                break;
        }
        this->timeBound = (float) (this->elementsInChunk) / (float) this->frequency / channels;

        /**
         * process spectrums
         */
        exec(data->get_name());
    } else throw "Null pointer to data";
}

/**
 * calculate spectrums to source
 */
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