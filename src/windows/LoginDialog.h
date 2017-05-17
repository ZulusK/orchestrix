#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <Game.h>
#include <QDialog>
#include <User.h>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
  Q_OBJECT

public:
  explicit LoginDialog(Game *game, QWidget *parent = 0);
  ~LoginDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

private:
  Ui::LoginDialog *ui;
  Game *environment;
};

#endif // LOGINDIALOG_H
