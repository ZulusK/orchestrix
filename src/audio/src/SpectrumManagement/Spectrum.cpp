//
// Created by zulus on 25.04.17.
//

#include <SpectrumManagement/Spectrum.h>
#include <AudioManagement/OpenAL.h>
#include <fftw3.h>
#include <cmath>


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
 * fill buffer B by normalized value of elements in buffer A
 * @param A input buffer
 * @param B output buffer
 * @param lenA count of elements in A
 * @param lenB count of elements in B
 * @param channel count of channel in A
 */
void fillBuffer(const __int16_t *A, double *B, size_t lenA, size_t lenB, int channel) {
    //find max element in A
    B[0] = A[0];
    double max = abs(A[0]);
    size_t iA = channel;
    size_t iB = 1;
    for (; iA < lenA && iB < lenB; iA += channel, iB++) {
        int a = A[iA];
        B[iB] = a;
        if (max < abs(A[iA])) {
            max = abs(A[iA]);
        }
    }
//    cout << iA << endl;
    if (max > 1) {
        //normalize elements and put it to B
        for (iB = 0, iA = 0; iA < lenA && iB < lenB; iA += channel, iB++) {
            B[iB] /= max;
        }
    }
    //add zero to end of B
    for (; iB < lenB; iB++) {
        B[iB] = 0;
    }
}


float *normalizeFFTBuffer(const fftw_complex *inputBuffer, size_t size) {
    float *outputBuffer = new float[size];
    for (size_t i = 0; i < size; i++) {
        outputBuffer[i] = hypot(inputBuffer[i][0], inputBuffer[i][1]);
    }
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
//        fillBuffer((__int8_t *) data + offset, chunkBuffer, inputDataLength - offset, chunkLength, channel);
    } else {
        fillBuffer((__int16_t *) data + offset, chunkBuffer, inputDataLength - offset, chunkLength, channel);
    }
//    this->exec(data, offset, chunkLength, inputDataLength, channel, bits);
    delete[] chunkBuffer;
}