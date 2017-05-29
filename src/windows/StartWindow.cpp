#include "StartWindow.h"
#include "ui_StartWindow.h"
#include <FileProcessing.h>
#include <GameDialog.h>
#include <HelpDialog.h>
#include <LoginDialog.h>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <ResultsDialog.h>
#include <iostream>
#include <qDebug>
using namespace std;

StartWindow::StartWindow(Game *game, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StartWindow) {
  ui->setupUi(this);
  this->showFullScreen();
  this->environment = game;
  connect(this, SIGNAL(updateWindow()), SLOT(updateContent()));
}

StartWindow::~StartWindow() {
  delete environment;
  delete ui;
}

void StartWindow::on_startBtn_clicked() {
  //  if (environment->getUser() == NULL) {
  on_loginBtn_clicked();

  qDebug() << "99999999";
  GameDialog *game_d = new GameDialog(environment);
  qDebug() << "888888888888";
  this->hide();

  if (!game_d->exec()) {
    this->close();
  }

  game_d->hide();
  this->show();
  delete game_d;
  QMessageBox::StandardButton reply;
  qDebug() << "yco ne horosho";
  reply = QMessageBox::question(this, "Saving", "Save your result?",
                                QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    qDebug() << "хорошо";
    ui->saveBtn->click();
  } else {
    qDebug() << "плохо";
  }
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

void StartWindow::on_helpBtn_clicked() {
  HelpDialog help_d(environment);
  this->hide();
  help_d.exec();
  this->show();
}

void StartWindow::on_loginBtn_clicked() {
  qDebug() << "+++++++++++++";
  LoginDialog log_d(environment);
  log_d.exec();
  qDebug() << environment->getUser()->getName();
}

void StartWindow::on_saveBtn_clicked() {
  qDebug() << "fhgfgjhfjhgf";
  FileProcessing *f = new FileProcessing;
  f->load("/Users/lena/projectX/res/results.json");
  users = f->users;

  auto user = environment->getUser();

  if (user != NULL) {
    users.push_back(user);
    f->write("/Users/lena/projectX/res/results.json");
  }
}

void StartWindow::on_logoutBtn_clicked() { environment->removeUser(); }
