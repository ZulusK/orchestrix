//
// Created by zulus on 04.04.17.
//

#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

#define REAL 0
#define IMAG 1

double getMaxValued(double *arr, long left, long right);

//return furie's spectrum
double *getSpectrum(double *inputBuff, long input_size, int max_db) {
    //   Compute corresponding number of complex output samples
    int output_size = (input_size / 2 + 1);
    // Allocate input and output buffers
    fftw_complex *fftBuff = static_cast<fftw_complex *>(fftw_malloc(output_size * sizeof(fftw_complex)));
    // Create plan
    //   Select plan creation flags
    //   see http://www.fftw.org/fftw3_doc/Planner-Flags.html#Planner-Flags
    int flags = FFTW_ESTIMATE;
    fftw_plan plan = fftw_plan_dft_r2c_1d(input_size,
                                          inputBuff,
                                          fftBuff,
                                          flags);
    fftw_execute(plan);
    double *outputData = (double *) malloc(sizeof(double) * input_size);
    if (outputData != NULL) {
        for (long i = 0; i < output_size; i++) {
            double v=sqrt(fftBuff[i][REAL]*fftBuff[i][REAL]+fftBuff[i][IMAG]*fftBuff[i][IMAG]);
            outputData[i] = max_db * log10(v);
//            printf("%.12lf\n",outputData[i]);
        };
    }
    fftw_free(fftBuff);
    fftw_destroy_plan(plan);
    return outputData;
}

//return max value from [left; rigth)
double getMaxValued(double *arr, long left, long right) {
    double max = arr[left];
    for (long i = left+1; i < right; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    return max;
}

//return max-amplituted chunks array
double *getSpectrumFrame(double *spectrum, long input_size, int frame_count, double min) {
    int range = (input_size / 2 + 1) / frame_count;
    double *chunks = (double *) malloc(sizeof(double) * frame_count);
    if (chunks == NULL) {
        return NULL;
    }
    for (long i = 0; i < frame_count; i++) {
        long rigth=(i+1)*range;
        chunks[i] = getMaxValued(spectrum, i * range, (rigth>=input_size)?input_size-1:rigth);
        if(chunks[i]<min) chunks[i]=min;
//        printf(" chunk %lf\n",chunks[i]);
    }
    return chunks;
}

