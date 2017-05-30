#ifndef GAME_H
#define GAME_H
#include <AudioData.h>
#include <AudioManager.h>
#include <AudioPlayer.h>
#include <FileProcessing.h>
#include <QMap>
#include <QPair>
#include <QString>
#include <User.h>

#define STORAGE_PATH "res/results.json"
/**
 * @brief The Game class defines class of game's environment
 */
class Game {
private:
  AudioManager *audioManager;
  QMap<QString, QPair<AudioData *, AudioPlayer *>> audioEffects;
  User *user;
  FileProcessing *storage;
  QString homepath;
  /**
   * @brief Game constructor
   */
  Game(AudioManager *manager, const QString &homepath);

public:
  /**
   * @brief init initialize game's environment
   * @return created game's env or null
   */
  static Game *init(const QString & homepath);
  /**
   *@brief ~Game  destructor
   */
  ~Game();
  /**
   * @brief addUser add user to game
   * @param user reference to created user
   */
  void addUser(User *user);
  /**
   * @brief removeUser remove user from game (next call getUser return null)
   */
  void removeUser();
  /**
   * @brief getUser get current player of game
   * @return User's reference if prsent or null
   */
  User *getUser();
  /**
   * @brief play try to play loaded sound by name
   * @param soundName name of sound
   */
  void play(const QString &soundName);

  void pause(const QString &soundName);
  /**
   * @brief getAudioManager get game's audio manager
   * @return game's audio manager
   */
  AudioManager *getAudioManager();
  /**
   * @brief loadSound load soud by name and add it to game sound manager
   * @param soundName path to sound file
   * @return true if success loaded, else - false
   */
  bool loadSound(const QString &soundName);

  bool saveStorage();
  bool updateStorage();
  FileProcessing *getStorage();
  QString getHomepath() const;
  void setHomepath(const QString &value);
  void stop(const QString &soundName);
};

#endif // GAME_H
