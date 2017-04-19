#include <stdio.h>

#if defined (__cplusplus)
extern "C" {
#endif
#include <progbase.h>
#include <pbconsole.h>
#if defined (__cplusplus)
}
#endif

#include <equalizer.h>
#include <stdlib.h>

#define STRIPE_H 5
#define STARTX 5
#define YDEFAULT 20       // Baseline for equalizer
#define MAX_DB 20
#define MIN_DB 0

typedef enum conAttribute_e Color;

struct Stripe {
    Color color;
    int x;
    int h;
};

void drawAudioSpectrum(Stripe *arr, int count) {
    for (int i = 0; i < count; i++) {

        drawStripe(arr + i);
    }
}

void drawStripe(Stripe *stripe) {
    for (int y = 0 ; y < stripe->h; y++) {
        conMove(YDEFAULT-y, stripe->x);
        conSetAttr(stripe->color);
        puts(" ");
    }
}

int *toHeightsArray(double *dbArray, int count) {

    int *heigthArray = (int *) malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        heigthArray[i] = dbArray[i] * STRIPE_H;
    }
    return heigthArray;
}

void Equalizer_startEqualizer(double *dbArray, int stripesCount, int db_value) {
    conHideCursor();
//    conResize(30,120);
    conSetAttr(BG_DEFAULT);
    conClear();
    Stripe stripeArr[stripesCount];
    int *heightsArray = toHeightsArray(dbArray,stripesCount); // Turning array of db into array of heights for stripes
    int currentColor =BG_INTENSITY_BLACK;
    for (int i = 0; i < stripesCount; i++) {
        stripeArr[i].x = STARTX+i;
        stripeArr[i].h = heightsArray[i];
        stripeArr[i].color = (Color) currentColor;
        currentColor++;
        if(currentColor==BG_INTENSITY_WHITE){
            currentColor=BG_INTENSITY_BLACK;
        }
    }
    free(heightsArray);
    drawAudioSpectrum(stripeArr,stripesCount);
    fflush(stdin);
}