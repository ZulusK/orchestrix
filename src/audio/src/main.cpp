//
// Created by zulus on 21.04.17.
//
#include <iostream>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>

using namespace std;

int main(void) {
    string filename = "res/21pilots.wav";
    AudioData *sound = AudioData::load(filename);
    cout << sound->toString() << endl;
    AudioManager *manager = AudioManager::init(1, 512);
    AudioPlayer *player = manager->getAudioPlayer(sound);
    manager->play(player);

    delete player;
    delete manager;
    delete sound;
}
