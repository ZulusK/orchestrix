#include "GameDialog.h"
#include "ui_GameDialog.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QTimer>
#include <iostream>
using namespace std;
GameDialog::GameDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();

  this->environment = game;
  //  this->audioData =
  //      AudioData::load(QFileDialog::getOpenFileName(
  //                          this, QString::fromUtf8("Choose your sound to
  //                          play"),
  //                          QDir::currentPath(), "Images (*.wav);;")
  //                          .toStdString());
  this->audioData = AudioData::load("../orchestrix/res/21pilots.wav");
  cout << audioData->toString() << endl;
  // create user sound
  this->audioPlayer = new AudioPlayer(game->getAudioManager(), audioData, 1);
  this->analyzer = new SpectrumAnalyzer(audioData, SAMPLE_4096, 50);
  // create equlizer view
  this->eqwidget = new EQWidget(audioPlayer, analyzer, this);
  ui->centralGrid->addWidget(eqwidget, 1, 0, 1, 2);
  audioPlayer->play();
}

GameDialog::~GameDialog() {
  delete audioPlayer;
  delete ui;
  delete eqwidget;
  delete audioData;
}
