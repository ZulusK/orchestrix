//
// Created by zulus on 04.04.17.
//

#ifndef TESTPROJ_AUDIOSPECTRUM_H
#define TESTPROJ_AUDIOSPECTRUM_H

double *getSpectrum(double *inputData, long frames, int max_db);
double *getSpectrumFrame(double *spectrum, long input_size, int chunk_count, double min);
#endif //TESTPROJ_AUDIOSPECTRUM_H
