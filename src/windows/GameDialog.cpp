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
  // create user sound
  this->audioPlayer = new AudioPlayer(game->getAudioManager(), audioData, 1);
  this->analyzer = new SpectrumAnalyzer(audioData, SAMPLE_4096, 50);
  // create equlizer view

  this->histogramm = new SoundHistogramm(audioPlayer, audioData, this);

  this->histogramm->setBrush(QBrush(QColor(0, 97, 255)));
  this->histogramm->setPen(
      QPen(QColor(0, 97, 255), 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  this->ui->centralGrid->addWidget(histogramm, 2, 0, 1, 2);

  this->eqwidget = new EQWidget(audioPlayer, analyzer, this);
  this->ui->centralGrid->addWidget(eqwidget, 1, 0, 1, 2);
  this->audioPlayer->play();
  this->eqwidget->setShape(AREA);
  this->eqwidget->setBrush(QBrush(QColor(0, 97, 255), Qt::Dense6Pattern));
  this->eqwidget->setPen(
      QPen(QColor(0, 97, 255), 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  this->eqwidget->setAntialiased(true);
  this->eqwidget->start();
}

GameDialog::~GameDialog() {
  delete audioPlayer;
  delete histogramm;
  delete ui;
  delete eqwidget;
  delete audioData;
}
