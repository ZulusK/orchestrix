#include "Game.h"
#include <QStringList>
#include <iostream>
using namespace std;
Game::Game(AudioManager *manager, const QString &homepath) {
  this->audioManager = manager;
  this->user = NULL;
  this->storage = new FileProcessing();
  this->homepath = homepath;
  updateStorage();
}

QString Game::getHomepath() const { return homepath; }

void Game::setHomepath(const QString &value) { homepath = value; }

Game::~Game() {
  storage->write(homepath + STORAGE_PATH);
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

void Game::removeUser() { this->user = NULL; }

User *Game::getUser() { return this->user; }

void Game::play(const QString &soundName) {
  if (audioEffects.contains(soundName)) {
    audioEffects[soundName].second->play();
  }
}

void Game::stop(const QString &soundName) {
  if (audioEffects.contains(soundName)) {
    audioEffects[soundName].second->stop();
  }
}

void Game::pause(const QString &soundName) {
  if (audioEffects.contains(soundName)) {
    audioEffects[soundName].second->pause();
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

Game *Game::init(const QString &homepath) {
  AudioManager *manager = AudioManager::init(20, 120);
  if (manager != NULL)
    return new Game(manager, homepath);
  else
    return NULL;
}

bool Game::saveStorage() {
  cout << storage->getUsers()->size() << endl;
  updateStorage();
  this->storage->write(homepath + STORAGE_PATH);
}

bool Game::updateStorage() { this->storage->load(homepath + STORAGE_PATH); }

FileProcessing *Game::getStorage() { return this->storage; }
