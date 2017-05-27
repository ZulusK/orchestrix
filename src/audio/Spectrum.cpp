#include <audio/AudioManager.h>
#include <audio/Spectrum.h>
#include <audio/SpectrumAnalyzer.h>
#include <cmath>

int Spectrum::getLength() const { return length; }

int inline getFFTSize(int mode) {
  int size;
  switch (mode) {
  case BASS_DATA_FFT8192:
    size = 4096;
    break;
  case BASS_DATA_FFT4096:
    size = 2048;
    break;
  case BASS_DATA_FFT2048:
    size = 1024;
    break;
  case BASS_DATA_FFT512:
    size = 256;
    break;
  case BASS_DATA_FFT1024:
  default:
    size = 512;
    break;
  }
  return size;
}

Spectrum::Spectrum(HCHANNEL hchannel, double offset, int mode, int bars) {
  this->length = bars;
  execute(hchannel, offset, mode, bars);
}

float *getFFT(HCHANNEL hchannel, double offset, int size, int mode) {
  float *fft = new float[size];
  for (int i = 0; i < size; i++) {
    fft[i] = 0;
  }
  BASS_ChannelSetPosition(hchannel, BASS_ChannelSeconds2Bytes(hchannel, offset),
                          BASS_POS_BYTE);
  BASS_ChannelGetData(hchannel, fft, mode);
  SpectrumAnalyzer::printError();
  //  for (int i = 0; i < size; i++) {
  //    fft[i] = sqrt(fft[i]);
  //  }
  return fft;
}

void Spectrum::execute(HCHANNEL hchannel, double offset, int mode, int bars) {
  int size = getFFTSize(mode);
  float *fft = getFFT(hchannel, offset, size, mode);
  calculateBars(fft, size);
  delete[] fft;
}

float *Spectrum::calculateBars(float *fft, int size) {
  this->spectrums = new float[this->length];
  this->energy = 0;

  int b0 = 0;
  for (int i = 0; i < length; i++) {
    int b1 = pow(2, i * 10.0 / (length - 1)); // determine size of the bin
    if (b1 > length - 1)
      b1 = length - 1;
    if (b1 <= b0)
      b1 = b0 + 1;
    int count = b1 - b0;
    float average = 0;
    // calculate energy and average value
    for (; b0 < b1; b0++) {
      average += sqrt(fft[b0]);
      energy += fft[b0];
    }
    this->spectrums[i] = sqrt(average / count);
  }
  return spectrums;
}

std::string Spectrum::toString() {
  std::string s = "Spectrum[ " + std::to_string(length) + " ]";
  for (int i = 0; i < length; i++) {
    s += std::to_string(spectrums[i]) + " ";
  }
  return s;
}

float *Spectrum::getSpectrums() const { return spectrums; }

Spectrum::~Spectrum() { delete[] spectrums; }

float Spectrum::getEnergy() const { return energy; }
