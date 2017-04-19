//
// Created by zulus on 04.04.17.
//

#include <wavFile.h>
#include <sndfile.hh>
#include <iostream>

using namespace std;

void WavFile_print(WavFile *wav) {
    Wavheader *header = &wav->header;
    cout << "=================HEADER START=================" << endl;
    cout << "Size of file(bytes): " << header->fileSize << endl;
    cout << "Format: " << header->formatStr[0] << header->formatStr[1] << header->formatStr[2] <<
         header->formatStr[3] << endl;
    cout << "Format type: " << ((header->audioFormat == 1) ? "PCM" : "Not PCM") << endl;
    cout << "Number of channels: " << header->numChannels << endl;
    cout << "Sampling frequency: " << header->sampleRate << " Hz" << endl;
    cout << "Byte per second: " << header->byteRate << endl;
    cout << "Block align (sample size) " << header->bytePerSample << endl;
    cout << "Sample depth " << header->bitsPerSample << endl;
    cout << "====================END======================= " << endl;
}

void normalizeWavData(WavFile *wav) {
    if (wav->datai != NULL) {
        long maxVal;
        switch (wav->header.bitsPerSample) {
            case 16:
                maxVal = INT16_MAX;
                break;
            default:
            case 8:
                maxVal = INT8_MAX;
                break;

        }
        wav->datad = (double *) malloc(sizeof(double) * wav->samples);
        if (wav->datad != NULL) {
            for (long i = 0; i < wav->samples; i++) {
                wav->datad[i] = wav->datai[i] / (double) maxVal;
            }
        }
    }
}

WavFile *WavFile_read(char *filename) {
    WavFile *wav = NULL;
    FILE *fin = fopen(filename, "r");
    if (fin == NULL) {
        return NULL;
    }
    wav = (WavFile *) malloc(sizeof(WavFile));
    if (wav == NULL) {
        fclose(fin);
        return NULL;
    }
    fread(&wav->header, sizeof(Wavheader), 1, fin);
    fclose(fin);
    readWavFilei(filename, wav);
    normalizeWavData(wav);
    if (wav->datai == NULL || wav->datad == NULL) {
        WavFile_free(wav);
        return NULL;
    }
    return wav;
}

void readWavFilei(const char *fname, WavFile *wav) {
    SndfileHandle file;
    file = SndfileHandle(fname);

    printf ("Opened file '%s'\n", fname) ;
    printf ("    Sample rate : %d\n", file.samplerate ()) ;
    printf ("    Channels    : %d\n", file.channels ()) ;
    if (file != NULL) {
        wav->datai = (__int16_t *) malloc(sizeof(__int16_t) * file.frames() * file.channels());
        if (wav->datai != NULL) {
            file.read(wav->datai, file.frames() * file.channels());
            wav->samples = file.frames();
//            for(long i=0; i<100;i++){
//                printf("????????%i\n",wav->datai[i]);
//            }
        }
    }
}

void WavFile_free(WavFile *wav) {
    if (wav != NULL) {
        if (wav->datad != NULL) {
            free(wav->datad);
        }
        if (wav->datai != NULL) {
            free(wav->datai);
        }
        free(wav);
    }
}


