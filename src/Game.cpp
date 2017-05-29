#include "Game.h"
#include <QStringList>
#include <iostream>
using namespace std;
Game::Game(AudioManager *manager) {
  this->audioManager = manager;
  this->user = NULL;
  this->storage = new FileProcessing();
  updateStorage();
}

Game::~Game() {
  storage->write(STORAGE_PATH);
  delete storage;
  for (auto it = audioEffects.begin(); it != audioEffects.end(); it++) {
    delete it.value().second;
    delete it.value().first;
  }
  delete this->audioManager;
}

void Game::addUser(User *user) {
  if (user) {
    this->user = user;
    storage->getUsers()->push_back(user);
  }
}

void Game::removeUser() {
  this->user = NULL;
}

User *Game::getUser() { return this->user; }

void Game::play(const QString &soundName) {
  cout << soundName.toStdString() << endl;
  if (audioEffects.contains(soundName) &&
      !audioEffects[soundName].second->isPlaying()) {
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
    cout << "Can't load " << soundName.toStdString() << endl;
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

bool Game::saveStorage() {
    cout<<storage->getUsers()->size()<<endl;
    updateStorage();
    this->storage->write(STORAGE_PATH);
}

bool Game::updateStorage() { this->storage->load(STORAGE_PATH); }

FileProcessing *Game::getStorage() { return this->storage; }
