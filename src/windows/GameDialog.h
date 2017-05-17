#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>

#include <Game.h>
#include <User.h>
namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog {
  Q_OBJECT

public:
  explicit GameDialog(Game *game, QWidget *parent = 0);
  ~GameDialog();

private:
  Ui::GameDialog *ui;
  Game *environment;
};

#endif // GAMEDIALOG_H
