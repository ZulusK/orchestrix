#include <QApplication>
#include <StartWindow.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Game *game = Game::init();
  if (game) {
    StartWindow w(game);
    w.show();
    a.exec();
    delete game;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
