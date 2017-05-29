#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <Game.h>
#include <QMainWindow>
#include <User.h>
namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit StartWindow(Game *game, QWidget *parent = 0);
  ~StartWindow();
signals:
  void updateWindow();
private slots:
  void on_startBtn_clicked();

  void on_resultsBtn_clicked();

  void updateContent();

  void on_helpBtn_clicked();

  void on_loginBtn_clicked();

  void on_saveBtn_clicked();

  void on_logoutBtn_clicked();

private:
  Ui::StartWindow *ui;
  Game *environment;
};

#endif // STARTWINDOW_H
