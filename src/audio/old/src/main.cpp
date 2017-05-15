#include <wavFile.h>
#include <audioSpectrum.h>
#include <playerWav.h>
#include <iostream>
#include <equalizer.h>

#if defined (__cplusplus)
extern "C" {
#endif
#include <progbase.h>
#include <pbconsole.h>
#if defined (__cplusplus)
}
#endif

#define MAX_DB 20
using namespace std;


int main(void) {
    WavFile *wav = WavFile_read("res/ass.wav");
//    WavFile *wav = WavFile_read("res/ppl.wav");
    if (wav != NULL) {
        WavFile_print(wav);
//        int N = 32768;
        int N = 2048;
        double *subChunk = (double *) malloc(sizeof(double) * N);
        long left = 0;
//        Player * player=Player_create(wav->datai,wav->samples,wav->header.numChannels,wav->header.sampleRate,wav->header.bitsPerSample);
        for (; left < wav->samples; left += N) {
            for (long i = 0; i < N; i++) {
                subChunk[i] = wav->datad[left + i * wav->header.numChannels];
            }
            double *spectrum = getSpectrum(subChunk, N, 1);
            double *frames = getSpectrumFrame(spectrum, N / 2, 64, 0);
            Equalizer_startEqualizer(frames, 64, 10);

//            Player_play(player);
            free(spectrum);
            free(frames);
            sleepMillis(100);
        }
        WavFile_free(wav);
    }
    return 0;
}



/*
 Player * player=Player_create(wav->datai, wav->samples, wav->header.numChannels, wav->header.sampleRate,
                                      wav->header.bitsPerSample);
        Player_play(player);
        Player_free(player);
 */