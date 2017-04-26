//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/Spectrum.h>
#include <AudioManagement/OpenAL.h>
#include <fftw3.h>
#include <cmath>
#include <AudioManagement/AudioManager.h>

#define MAX_DB 100

int Spectrum::getLength() const {
    return length;
}

/**
 * fill buffer B by normalized value of elements in buffer A
 * @param A input buffer
 * @param B output buffer
 * @param lenA count of elements in A
 * @param lenB count of elements in B
 * @param channel count of channel in A
 */
void Spectrum::fillBuffer(const __int16_t *A, double *B, size_t lenA, size_t lenB, int channel) {
    size_t iA = 0;
    size_t iB = 0;
    for (; iA < lenA && iB < lenB; iA += channel, iB++) {
        B[iB] = 0;
        for (int i = 0; i < channel; i++) {
            B[iB] += A[iA];
        }
        B[iB] /= channel * INT16_MAX;
    }
    for (; iB < lenB; iB++) {
        B[iB] = 0;
    }
}

/**
 * fill buffer B by normalized value of elements in buffer A
 * @param A input buffer
 * @param B output buffer
 * @param lenA count of elements in A
 * @param lenB count of elements in B
 * @param channel count of channel in A
 */
void Spectrum::fillBuffer(const __int8_t *A, double *B, size_t lenA, size_t lenB, int channel) {
    size_t iA = 0;
    size_t iB = 0;
    for (; iA < lenA && iB < lenB; iA += channel, iB++) {
        B[iB] = 0;
        for (int i = 0; i < channel; i++) {
            B[iB] += A[iA];
        }
        B[iB] /= channel * INT8_MAX;
    }
    for (; iB < lenB; iB++) {
        B[iB] = 0;
    }
}

float *normalizeFFTBuffer(fftw_complex *inputBuffer, size_t size) {
    float *outputBuffer = new float[size];
    for (size_t i = 0; i < size; i++) {
        outputBuffer[i] = 10 * log10(hypot(inputBuffer[i][0], inputBuffer[i][1]));
    }
    return outputBuffer;
}

/**
 * create new spectrum from input data
 * @param data reference to data
 * @param offset offset to start of current analyzed data
 * @param chunk size of buffer
 * @param elementInSpectrum elements in output spectrum
 * @param inputDataLength count of elements in input buffer
 * @param channel channels in sound
 * @param bits bits per sample
 */
Spectrum::Spectrum(const void *data, size_t offset, size_t chunkLength, int bars, size_t inputDataLength,
                   int channel, int bits) {
    this->length = bars;

    //create new buffer
    double *chunkBuffer = new double[chunkLength];
    //fill it by normalized data
    if (bits == 8) {
        fillBuffer((__int8_t *) data + offset, chunkBuffer, inputDataLength - offset, chunkLength, channel);
    } else {
        fillBuffer((__int16_t *) data + offset, chunkBuffer, inputDataLength - offset, chunkLength, channel);
    }
    this->exec(chunkBuffer, chunkLength);
    delete[] chunkBuffer;
}

/**
 * calculate bars by average value of soe range of elements
 * @param buffer
 * @param size
 * @return
 */
float *Spectrum::createBars(float *frequenceBuffer, int size) {
    int range = size / this->length;
    float *barVal = new float[length];
    for (int i = 0; i < length; i++) {
        int rigthBound = (i + 1) * range;
        int leftBound = i * range;
        double average = 0;
        for (int j = leftBound; j < rigthBound; j++) {
            if (frequenceBuffer[j] > 0)
                average += frequenceBuffer[j];
        }
        average /= range;
        barVal[i] = average;
    }
    //normalize bars
    for (int i = 0; i < length; i++) {
        barVal[i] /= (double) MAX_DB;
    }
    return barVal;
}

/**
 * execute calculating fft value and spectrums
 * @param input_buffer
 * @param input_size
 * @param bars
 */
void Spectrum::exec(double *input_buffer, size_t input_size) {
    int output_size = (input_size / 2 + 1);
    fftw_complex *output_buffer = static_cast<fftw_complex *>(fftw_malloc(output_size * sizeof(fftw_complex)));
    /**
     * create plan
     */
    int flags = FFTW_ESTIMATE;
    fftw_plan plan = fftw_plan_dft_r2c_1d(input_size, input_buffer, output_buffer, flags);
    fftw_execute(plan);
    float *bufferOfFreq = normalizeFFTBuffer(output_buffer, output_size);
    this->spectrums = createBars(bufferOfFreq, output_size);
    /**
     * free resources
     */
    fftw_free(output_buffer);
    fftw_destroy_plan(plan);
    delete[] bufferOfFreq;
}

string Spectrum::toString() {
    string s = "Spectrum[ " + to_string(length) + " ]";
    for (int i = 0; i < length; i++) {
        s += to_string(spectrums[i]) + " ";
    }
    return s;
}

float *Spectrum::getSpectrums() const {
    return spectrums;
}
