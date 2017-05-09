//
// Created by zulus on 09.05.17.
//

#ifndef ORCHESTRIX_CONSOLEEQUALIZER_H
#define ORCHESTRIX_CONSOLEEQUALIZER_H

#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <GraphicPlane.h>
#include <GraphUtil.h>

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
public:
    ConsoleEqualizer(AudioData *sound, int heigth, int count, CursorAttributes *colors = NULL);

    void exec();

    virtual ~ConsoleEqualizer();

    void drawBar(int ind, double val);

    void clearBar(int ind, double val);

    void drawEQ(int ind);

    void clearEQ(int ind);

    double getBarHeight(double val);

    double calculateSum(int ind);
};


#endif //ORCHESTRIX_CONSOLEEQUALIZER_H
