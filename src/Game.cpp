#include "Game.h"
#include <QStringList>
#include <iostream>
using namespace std;
Game::Game(AudioManager *manager) {
  this->audioManager = manager;
  this->user = NULL;
}

Game::~Game() {
  for (auto it = audioEffects.begin(); it != audioEffects.end(); it++) {
    delete it.value().second;
    delete it.value().first;
  }
  delete this->audioManager;
  if (user) {
    delete this->user;
  }
}

void Game::addUser(User *user) { this->user = user; }

void Game::removeUser() {
  if (this->user != NULL) {
    delete this->user;
  }
  this->user = NULL;
}

User *Game::getUser() { return this->user; }

void Game::play(const QString &soundName) {
  cout << soundName.toStdString() << endl;
  if (audioEffects.contains(soundName)) {
    audioEffects[soundName].second->stop();
    audioEffects[soundName].second->play();
  }
}

AudioManager *Game::getAudioManager() { return this->audioManager; }

bool Game::loadSound(const QString &soundName) {
  QStringList list = soundName.split("/");
  QString name = list.at(list.size() - 1);

  if (this->audioEffects.contains(name)) {
    return false;
  }

  auto sound = AudioData::load(soundName.toStdString());
  if (sound == NULL) {
    cout << "not loaded " << soundName.toStdString() << endl;
    return false;
  }
  audioEffects[name].first = sound;
  audioEffects[name].second = new AudioPlayer(audioManager, sound, 1);
  return true;
}

Game *Game::init() {
  AudioManager *manager = AudioManager::init(20, 120);
  if (manager != NULL)
    return new Game(manager);
  else
    return NULL;
}
