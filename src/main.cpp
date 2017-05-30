#include <QApplication>
#include <StartWindow.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Game *game = Game::init("../orchestrix/");
  if (game) {
    StartWindow w(game,"../orchestrix/res/Stressed Out.wav");
    w.show();
    a.exec();
    delete game;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
