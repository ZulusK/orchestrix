//
// Created by zulus on 09.05.17.
//

#include <progbase-cpp/console.h>
#include "ConsoleGraphic/ConsoleEqualizer.h"

#define WIDTH 3
#define SHOOT 0.6
#define SIZE_MULT 100

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
    this->sound = sound;
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

void ConsoleEqualizer::drawInfo(long ind) {
    static int color = 0;
    long millisecEQ = analyzer->getTimeBound() * 1000 * ind;
    int secEQ = millisecEQ / 1000;
    int minEQ = secEQ / 60;
    secEQ %= 60;
    millisecEQ %= 1000;

    long millisecPlayer = player->getTime();
    int secPlayer = millisecPlayer / 1000;
    int minPlayer = secPlayer / 60;
    secPlayer %= 60;
    millisecPlayer %= 1000;

    console->print(std::to_string(minPlayer) + ":" + std::to_string(secPlayer) + ":" + std::to_string(millisecPlayer) +
                   " / " + std::to_string(minEQ) + ":" + std::to_string(secEQ) + ":" + std::to_string(millisecEQ),
                   console->getDefaultColorBG(), console->getDefaultColorFG(),
                   Vec2D{console->getWidth() - 26, 1});
    console->print(std::to_string(analyzer->getSHOOT()),
                   console->getDefaultColorBG(), console->getDefaultColorFG(),
                   Vec2D{console->getWidth() - 26, 2});
    console->print(sound->toString(), console->getDefaultColorBG(), console->getDefaultColorFG(),
                   Vec2D{console->getWidth() - 26, 4});

    double valNew = getBarHeight(getEnergy(ind) / 10);
    double valOld = getBarHeight(getEnergy(ind - 1) / 10);
    console->fillRect(Vec2D{1, lowBound}, Vec2D{1 + WIDTH, lowBound - heigth * valOld},
                      console->getDefaultColorBG());
    console->fillRect(Vec2D{1, lowBound}, Vec2D{1 + WIDTH, lowBound - heigth * valNew},
                      barColors[color]);
    if (isShoot(ind)) {
        color++;
        color %= barsCount;
    }
}

bool ConsoleEqualizer::isShoot(int ind) {
    return analyzer->isShoot(ind);
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
        drawInfo(i);
        drawEQ(i);
//        console->print(std::to_string(i), console->getDefaultColorBG(), color, Vec2D{1, 1});
        console->redraw();
        timeDif = timeBound - (clock() - time0) / (double) CLOCKS_PER_SEC * 1000;
        long playerTime = player->getTime();
        if (timeDif > 0) {
            this_thread::sleep_for(chrono::milliseconds(timeDif));
        }

        clearEQ(i);
        time0 = clock();
    }

    player->stop();
}


double ConsoleEqualizer::getEnergy(int ind) {
    if (ind < 0 || ind >= analyzer->getSpectrums().size()) {
        return 0.0001;
    }
    return analyzer->getSpectrums()[ind]->getEnergy();
}

void ConsoleEqualizer::detectEnergy(int ind) {

}
