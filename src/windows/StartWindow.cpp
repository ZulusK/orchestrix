#include "StartWindow.h"
#include "ui_StartWindow.h"
#include <GameDialog.h>
#include <HelpDialog.h>
#include <LoginDialog.h>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <ResultsDialog.h>
#include <iostream>
using namespace std;

StartWindow::StartWindow(Game *game, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StartWindow) {
  ui->setupUi(this);
  this->showFullScreen();
  this->environment = game;
  connect(this, SIGNAL(updateWindow()), SLOT(updateContent()));
  QPalette *palette = new QPalette();
  palette->setBrush(this->backgroundRole(), QBrush(QPixmap(":/res/fon.jpg")));
  this->setPalette(*palette);
  updateContent();
}

StartWindow::~StartWindow() {
  delete ui;
}

void StartWindow::on_startBtn_clicked() {
  // if user not logined yet
  // then login him
  if (environment->getUser() == NULL) {
    on_loginBtn_clicked();
  }
  // create new game window
  GameDialog *game_d = new GameDialog(environment);
  // execute game
  this->hide();
  game_d->exec();
  this->show();
  // delete window (stop playing music)
  delete game_d;
  // update labels on window
  updateContent();
  // ask, is user wont to save result
  QMessageBox::StandardButton saveDialog;
  saveDialog = QMessageBox::question(this, "Saving", "Save your result?",
                                     QMessageBox::Yes | QMessageBox::No);
  if (saveDialog == QMessageBox::Yes) {
    ui->saveBtn->click();
  }
}

void StartWindow::on_resultsBtn_clicked() {
  this->hide();
  ResultsDialog res_d(environment);
  res_d.exec();
  this->show();
}

void StartWindow::updateContent() {
  if (environment->getUser() != NULL) {
    ui->nameLbl->setText(environment->getUser()->getName());
    ui->scoreLbl->setText(QString::number(environment->getUser()->getScore()));
  } else {
    ui->nameLbl->setText("Not logined yes");
    ui->scoreLbl->setText("");
  }
}

void StartWindow::on_helpBtn_clicked() {
  HelpDialog help_d(environment);
  this->hide();
  help_d.exec();
  this->show();
}

void StartWindow::on_loginBtn_clicked() {
  LoginDialog log_d(environment);
  log_d.exec();
  qDebug() << environment->getUser()->getName();
  // update labels on window
  updateContent();
}

void StartWindow::on_saveBtn_clicked() {
  auto user = environment->getUser();
  if (user != NULL) {
     environment->saveStorage();
  }
}

void StartWindow::on_logoutBtn_clicked() {
  environment->removeUser();
  // update labels on window
  updateContent();
}
