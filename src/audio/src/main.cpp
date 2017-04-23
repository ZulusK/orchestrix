//
// Created by zulus on 21.04.17.
//
#include <iostream>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioPlayer.h>

#define _DEBUG
using namespace std;

int main(void) {
    string filename1 = "res/mySound.wav";
    AudioData *sound1 = AudioData::load(filename1);
    string filename2 = "res/ppl.wav";
    AudioData *sound2 = AudioData::load(filename2);
    AudioManager *manager = AudioManager::init(1, 8);
//    manager->printFreeSources();
    AudioPlayer player1(manager, sound1, 1);
    cout << player1.toString() << endl;
    player1.play();
    while (1) {
    }

    delete manager;
    delete sound1;
}
