//
// Created by zulus on 09.05.17.
//

#ifndef ORCHESTRIX_CONSOLEEQUALIZER_H
#define ORCHESTRIX_CONSOLEEQUALIZER_H

#include <audio/SpectrumAnalyzer.h>
#include <graphic/GraphicPlane.h>
#include <graphic/GraphUtil.h>
#include <vector>

class ConsoleEqualizer {
    SpectrumAnalyzer *analyzer;
    AudioPlayer *player;
    AudioManager *manager;
    GraphicPlane *console;
    __int32_t currentPos;
    int heigth;
    int width;
    int shift;
    int lowBound;
    int barsCount;
    CursorAttributes *barColors;
    int samplesInSpectrums = 2048;
    std::vector<unsigned long> energy;
    AudioData *sound;
public:
    ConsoleEqualizer(AudioData *sound, int heigth, int count, CursorAttributes *colors = NULL);

    void exec();

    virtual ~ConsoleEqualizer();

private:

    void drawBar(int ind, double val);

    void clearBar(int ind, double val);

    void drawEQ(int ind);

    void clearEQ(int ind);

    double getBarHeight(double val);

    double calculateSum(int ind);

    void drawInfo(long ind);


    void detectEnergy(int ind);

    double getEnergy(int ind);

    bool isShoot(int ind);
};


#endif //ORCHESTRIX_CONSOLEEQUALIZER_H
