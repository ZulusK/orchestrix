//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/Spectrum.h>
#include <AudioManagement/OpenAL.h>
#include <fftw3.h>
#include <cmath>

float *Spectrum::getSpecrtums() const {
    return specrtums;
}

float Spectrum::getMax() const {
    return max;
}

float Spectrum::getMin() const {
    return min;
}

int Spectrum::getLength() const {
    return length;
}

/**
 * normalize input data (16 bit)
 * @param data reference to raw data
 * @param chunkCount count of elements in data
 * @param length elements in output  array
 * @param channels count of channels in data
 * @return normalized array
 */
double *normalizeData16(const __int16_t *data, size_t chunkCount, size_t length, int channels) {

}


/**
 * normalize input data (8 bit)
 * @param data reference to raw data
 * @param chunkCount count of elements in data
 * @param length elements in output  array
 * @return normalized array
 */
double *normalizeData8(const __int8_t *data, size_t chunkCount, size_t length) {
    /**
     * search for max value
     */
    float max = data[0];
    for (size_t i = 1; i < chunkCount && i < length; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    float *dest = new float[length];
    size_t i;
    /**
     * copy elements
     */
    for (i = 0; i < chunkCount && i < length; i++) {
        dest[i] = data[i] / max;
    }
    /**
     * add zeroes at the end
     */
    for (; i < length; i++) {
        dest[i] = 0;
    }
    return dest;
}

float *normalizeFFTBuffer(fftw_complex *inputBuffer, size_t size) {
    float *outputBuffer = new float[size];
    for (size_t i = 0; i < size; i++) {
        outputBuffer[i] = hypot(inputBuffer[i][0], inputBuffer[i][1]);
    }
}

void Spectrum::exec(double *input_buffer, size_t input_size) {
    /*
     * Compute corresponding number of complex output samples
     */
    length = (input_size / 2 + 1);

    /*
     * Allocate input and output buffers
     */
    fftw_complex *output_buffer = static_cast<fftw_complex *>(fftw_malloc(length * sizeof(fftw_complex)));

    /*
     * Create plan
     * Select plan creation flags
     */
    int flags = FFTW_ESTIMATE;
    fftw_plan plan = fftw_plan_dft_r2c_1d(input_size,
                                          input_buffer,
                                          output_buffer,
                                          flags);
    float *normalizeFFT = normalizeFFTBuffer(output_buffer, length);
    fftw_execute(plan);
    fftw_free(output_buffer);
    fftw_destroy_plan(plan);
}

/**
 * create new Spectrum and analyze it
 * @param data reference to raw data
 * @param offset offset from start
 * @param chunk count of elements in spectrum
 * @param info information about sound
 */
Spectrum::Spectrum(const void *data, size_t offset, size_t chunk, const AudioInfo &info) {
    double *normalizedData = NULL;
    if (info.format == AL_FORMAT_STEREO16 || info.format == AL_FORMAT_MONO16) {
        normalizedData = normalizeData16((__int16_t *) data + offset, info.samples - offset, chunk);
    } else {
        normalizedData = normalizeData8((__int8_t *) data + offset, info.samples - offset, chunk);
    }
    exec(chunk);
}