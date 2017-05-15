#ifndef EQUALIZER_H
#define EQUALIZER_H


typedef struct Stripe Stripe;


void drawStripe(Stripe * stripe);       // Draws a single stripe of equalizer, given stripe structure(x , y , color)
void drawAudioSpectrum(Stripe *arr, int);  // Iterates through Stripe array calling drawStripe() for each stripe
int *toHeightsArray(double dbArray[], int count); //Converts array of db floats into array of heights
void Equalizer_startEqualizer(double *dbArray,int,int); // Function that is invoked from outside

#endif