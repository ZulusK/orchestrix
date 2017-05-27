#include <QApplication>
#include <StartWindow.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Game *game = Game::init();
  if (game) {
    StartWindow w(game);
    w.show();
    return a.exec();
  } else {
    return EXIT_FAILURE;
  }
}
