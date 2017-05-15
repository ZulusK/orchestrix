#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <src/gameplay/Game.h>
#include <QDialog>

namespace Ui {
class MenuDialog;
}

class MenuDialog : public QDialog {
  Q_OBJECT
public:
  explicit MenuDialog(Game *environment, QWidget *parent = 0);
  ~MenuDialog();

private:
  Ui::MenuDialog *ui;
  Game *environment;
};

#endif // MENUDIALOG_H
