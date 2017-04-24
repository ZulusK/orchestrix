//
// Created by zulus on 21.04.17.
//
#include <iostream>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioPlayer.h>
#include <thread>
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
//    AudioPlayer player2(manager, sound2, 3);
    cout << player1.toString() << endl;
    thread * t1=player1.play();
//    thread * t2=player2.play();
    t1->join();
    cout<<"don't wait"<<endl;
    while(player1.isPlaying());
//    t2->join();
    delete t1;
    delete manager;
    delete sound1;
}
