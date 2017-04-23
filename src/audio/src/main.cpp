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
    string filename = "res/ppl.wav";
    AudioData *sound = AudioData::load(filename);
    cout << sound->toString() << endl;
    AudioManager *manager = AudioManager::init(1, 8);
//    manager->printBuffers();
//    manager->printSources();
    AudioPlayer player(manager, sound, 1);
    player.play();
    while (1) {
        cout<<"llop"<<endl;
    }

    delete manager;
    delete sound;
}
