#ifndef GAME_H
#define GAME_H
#include <AudioData.h>
#include <AudioManager.h>
#include <AudioPlayer.h>
#include <QMap>
#include <QPair>
#include <QString>
#include <User.h>
class Game {
private:
  AudioManager *audioManager;
  QMap<QString, QPair<AudioData *, AudioPlayer *>> audioEffects;
  User *user;

public:

  void addUser(User *user);
  void removeUser();
  void play(const QString &soundName);
  AudioManager *getAudioManager();
  void loadSound(const QString &soundName);

};

#endif // GAME_H
