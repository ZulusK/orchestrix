//
// Created by zulus on 09.05.17.
//

#include <progbase-cpp/console.h>
#include "ConsoleGraphic/ConsoleEqualizer.h"

#define WIDTH 3
#define SHOOT 0.3
#define SIZE_MULT 10000

CursorAttributes *copyColors(CursorAttributes *colors, int cnt, CursorAttributes defColor) {
    CursorAttributes *newColors;
    newColors = new CursorAttributes[cnt];
    srand(time(NULL));
    if (!colors) {
        for (int i = 0; i < cnt; i++) {
            newColors[i] = GraphicPlane::getRandomBGColor();
            if (newColors[i] == defColor) {
                i--;
            }
        }

    } else {
        for (int i = 0; i < cnt; i++)
            newColors[i] = colors[i];
    }
    return newColors;
}

ConsoleEqualizer::ConsoleEqualizer(AudioData *sound, int heigth, int barsCount, CursorAttributes *colors) {
    manager = AudioManager::init();
    player = new AudioPlayer(manager, sound);
    this->width = max(barsCount * WIDTH, 120);
    this->heigth = heigth;
    this->shift = (width - barsCount * WIDTH) / 2;
    this->barsCount = barsCount;

    console = new GraphicPlane(width, heigth + 5, pb::BG_INTENSITY_BLACK);
    analyzer = new SpectrumAnalyzer(sound, SAMPLE_2048, barsCount);
    this->lowBound = console->getHeigth() - 2;
    this->barColors = copyColors(colors, barsCount, console->getDefaultColorBG());
    this->currentPos = 0;
}

ConsoleEqualizer::~ConsoleEqualizer() {
    player->stop();
    delete[] barColors;
    delete player;
    delete console;
}

void ConsoleEqualizer::drawBar(int ind, double val) {
    double barH = heigth * val;
    console->fillRect(Vec2D{shift + ind * WIDTH, lowBound}, Vec2D{shift + ind * WIDTH + WIDTH, lowBound - heigth * val},
                      barColors[ind]);
}

void ConsoleEqualizer::clearBar(int ind, double val) {
    double barH = heigth * val;
    console->fillRect(Vec2D{shift + ind * WIDTH, lowBound}, Vec2D{shift + ind * WIDTH + WIDTH, lowBound - heigth * val},
                      console->getDefaultColorBG());
}

void ConsoleEqualizer::drawEQ(int ind) {
    auto currSpec = analyzer->getSpectrums()[ind]->getSpectrums();
    auto color = GraphicPlane::getRandomFGColor();
    for (int i = 0; i < analyzer->getBars(); i++) {
        drawBar(i, getBarHeight(currSpec[i]));
//        console->print(std::to_string(i) + " " + std::to_string(getBarHeight(currSpec[i])), console->getDefaultColorBG(), color,
//                       Vec2D{1, 1 + i});
    }
}

double ConsoleEqualizer::getBarHeight(double val) {
    double H = (val * SIZE_MULT);
    H = ((H > heigth) ? heigth : H) / (double) heigth;
    return H;
}

void ConsoleEqualizer::clearEQ(int ind) {
    auto currSpec = analyzer->getSpectrums()[ind]->getSpectrums();
    for (int i = 0; i < analyzer->getBars(); i++) {
        clearBar(i, getBarHeight(currSpec[i]));
    }
}

void ConsoleEqualizer::exec() {
    console->prepare();
    long time0;
    long timeDif;
    long timeBound = 1000 * analyzer->getTimeBound();
    player->play();
    auto color = GraphicPlane::getRandomFGColor();
    int frames = analyzer->getSpectrums().size();
    time0 = clock();
    auto t1 = clock();
    int pos = 1;
    for (unsigned long i = 0; i < frames; i++) {
        drawEQ(i);
        console->print(std::to_string(i), console->getDefaultColorBG(), color, Vec2D{1, 1});
        timeDif = timeBound - (clock() - time0) / (double) CLOCKS_PER_SEC * 1000;
        console->redraw();
        if (timeDif > 0) {
            this_thread::sleep_for(chrono::milliseconds(timeDif));
        }
        float lastEnergy = 0;
        if (i - 1 < 3) {
            lastEnergy = 0.0000001;
        } else {
            lastEnergy = analyzer->getSpectrums()[i+1]->getEnergy() + 0.00001;
        }
        float currEnergy = analyzer->getSpectrums()[i]->getEnergy() + 0.00001;

        if (currEnergy / lastEnergy < SHOOT) {
            console->print(std::to_string(lastEnergy) +std::to_string(currEnergy), console->getDefaultColorBG(), color, Vec2D{pos, 3});
            delete[]this->barColors;
            this->barColors = copyColors(NULL,barsCount,console->getDefaultColorBG());
            console->redraw();
        }
        clearEQ(i);
        double playerTime = player->getTime();
        time0 = clock();
    }
    console->redraw();
    player->stop();
}

