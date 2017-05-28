#include "StartWindow.h"
#include "ui_StartWindow.h"
#include <GameDialog.h>
#include <HelpDialog.h>
#include <LoginDialog.h>
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
  QPalette * palette = new QPalette();
  palette->setBrush(this->backgroundRole(), QBrush(QPixmap(":/res/fon.jpg")));
  this->setPalette(*palette);

}

StartWindow::~StartWindow() {
  delete environment;
  delete ui;
}

void StartWindow::on_startBtn_clicked() {
  GameDialog *game_d = new GameDialog(environment);
  this->hide();
  if (!game_d->exec()) {
    this->close();
  }
  game_d->hide();
  this->show();
  delete game_d;
  cout<<"E"<<endl;
//  QMessageBox::StandardButton reply;
//  reply = QMessageBox::question(this, "Saving", "Save your result?",
//                                QMessageBox::Yes | QMessageBox::No);
//  if (reply == QMessageBox::Yes) {
//    cout << "Yes was clicked" << endl;
//    ui->saveBtn->click();
//  } else {
//    cout << "Yes was *not* clicked" << endl;
//  }
  cout<<"F"<<endl;
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
  LoginDialog log_d(environment);
  if (!log_d.exec()) {
    this->close();
  }
}

void StartWindow::on_saveBtn_clicked()
{

}
