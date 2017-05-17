#include "StartWindow.h"
#include "ui_StartWindow.h"
#include <GameDialog.h>
#include <HelpDialog.h>
#include <LoginDialog.h>
#include <QDir>
#include <QFileDialog>
#include <ResultsDialog.h>

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StartWindow) {
  ui->setupUi(this);
  this->showFullScreen();
  this->environment = new Game();
  connect(this, SIGNAL(updateWindow()), SLOT(updateContent()));
}

StartWindow::~StartWindow() { delete ui; }

void StartWindow::on_startBtn_clicked() {

  GameDialog game_d(environment);
  this->hide();
  if (!game_d.exec()) {
    this->close();
  }
  this->show();
}

void StartWindow::on_resultsBtn_clicked() {
  this->hide();
  ResultsDialog res_d(environment);
  // if window was closing
  if (!res_d.exec()) {
    this->close();
  }
  this->show();
}

void StartWindow::updateContent() {}

void StartWindow::on_settingsBtn_clicked() {}

void StartWindow::on_helpBtn_clicked() {
  HelpDialog help_d(environment);
  this->hide();
  help_d.exec();
  this->show();
}

void StartWindow::on_loginBtn_clicked() {
  LoginDialog log_d(environment);
  if (!log_d.exec()) {
    this->close();
  }
}
