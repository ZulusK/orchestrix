//
// Created by zulus on 21.04.17.
//
#include <iostream>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>
#define _DEBUG
using namespace std;

int main(void) {
    string filename = "res/ppl.wav";
    AudioData *sound = AudioData::load(filename);
    cout << sound->toString() << endl;
    AudioManager *manager = AudioManager::init(1, 8);
    manager->printBuffers();
    manager->printSources();

    delete manager;
    delete sound;
}
