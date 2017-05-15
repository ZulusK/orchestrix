#include "Game.h"

Game::Game() {
  this->player = new User("", 0);
  this->audioManager = AudioManager::init(10, 100);
}

/**
 * @brief Game::exec show menu window and case next executing step
 * @param argc count of commant-line arguments
 * @param argv commant-line arguments
 * @return status of QApplicaton
 */
int Game::exec(int argc, char **argv) {
  QApplication a(argc, argv);
  bool stop = false;
  while (!stop) {
    MenuDialog *menu_w(this);
    int status = menu_w->exec();
    switch (status) {
    case START_INPUT:
      break;
    case HELP_INPUT:
      break;
    case SHOW_RESULTS_INPUT:
      break;
    case LOGIN_INPUT:
      break;
    case EXIT_INPUT:
    default:
      stop = true;
      break;
    }
    delete menu_w;
  }
  return a.exec();
}

Game::~Game() {
  save();
  delete this->player;
  delete this->audioManager;
}
