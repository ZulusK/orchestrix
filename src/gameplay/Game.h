#ifndef GAME_H
#define GAME_H

#include <AudioManager.h>
#include <Controller.h>
#include <GameDialog.h>
#include <HelpDialog.h>
#include <LoginDialog.h>
#include <MenuDialog.h>
#include <QApplication>
#include <ResultsDialog.h>
#include <User.h>

enum {
  START_INPUT = 0xABCD,
  SHOW_RESULTS_INPUT,
  EXIT_INPUT,
  HELP_INPUT,
  LOGIN_INPUT
};

class Game {
  /**********************
   * game objects
   *********************/
  User *player;
  Controller *controller;
  AudioManager *audioManager;

public:
  Game();
  ~Game();
  int exec(int argc, char **argv);
  int showMenu();
  int showLogin();
  int showScore();
  int showGame();
  int showHelp();
  void save(User *player = NULL);
};

#endif // GAME_H
