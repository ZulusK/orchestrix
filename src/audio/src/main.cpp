//
// Created by zulus on 21.04.17.
//
#include <iostream>
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioPlayer.h>
#include <thread>
#include <pbconsole.h>
#include <SpectrumManagement/SpectrumAnalyzer.h>

#define _DEBUG
using namespace std;

void exampleSound() {
    string filename1 = "res/mySound.wav";
    AudioData *sound1 = AudioData::load(filename1);
    string filename2 = "res/ppl.wav";
    AudioData *sound2 = AudioData::load(filename2);
    AudioManager *manager = AudioManager::init(1, 8);
    AudioPlayer *player1 = new AudioPlayer(manager, sound1, 1);
    AudioPlayer *player2 = new AudioPlayer(manager, sound2, 3);
    cout << player1->toString() << endl;
    thread *t1 = player1->play();
    thread *t2 = player2->play();
    while (player2->isPlaying() || player1->isPlaying()) {
        cout << "input<<" << endl;
        if (conIsKeyDown()) {
            char input = conGetChar();
            if (input == '1') {
                if (player1->isPaused()) {
                    cout << "try to rewind 1" << endl;
                    t1 = player1->rewind();
                } else {
                    cout << "try to pause 1" << endl;
                    player1->pause();
                    t1->join();
                    delete (t1);
                }
            } else if (input == '2') {
                if (player2->isPaused()) {
                    t2 = player2->rewind();
                } else {
                    player2->pause();
                    delete (t1);
                }
            }
        }
    }
    t1->join();
    t2->join();
    cout << "don't wait" << endl;
    while (player1->isPlaying());

    delete t1;
    delete player1;
    delete manager;
    delete sound1;
}

int main(void) {
//    exampleSound();
    string filename1 = "res/21pilots.wav";
    AudioData *sound1 = AudioData::load(filename1);
    cout<<sound1->toString()<<endl;
    SpectrumAnalyzer analyzer(sound1, 10000, 20);

}
