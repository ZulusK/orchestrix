#include "GameDialog.h"
#include "ui_GameDialog.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
using namespace std;

QString GameDialog::loadSound() {
  QString soundPath = QFileDialog::getOpenFileName(
      this, QString::fromUtf8("Choose your sound to play"), QDir::currentPath(),
      "Images (*.wav);;");
  if (soundPath.length() == 0) {
    soundPath = "../orchestrix/res/21pilots.wav";
  }
  // load sound
  this->audioData = AudioData::load(soundPath.toStdString());

  // create sound player
  this->audioPlayer =
      new AudioPlayer(environment->getAudioManager(), audioData, 2);

  this->analyzer = new SpectrumAnalyzer(audioData, SAMPLE_1024, 50);
  //  this->environment->getUser()->setSoundName(soundPath);
  return soundPath;
}

void GameDialog::init() {
  // load sound
  loadSound();

  // create equlizer view
  this->eqDefPen = new QPen(QColor("#2196F3"), 10, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin);
  this->eqDefBrush = new QBrush(QColor("#2196F3"), Qt::Dense6Pattern);
  this->eqBadBrush = new QBrush(QColor(255, 20, 0), Qt::Dense6Pattern);
  this->eqGoodBrush = new QBrush(QColor(0, 255, 20), Qt::Dense6Pattern);

  this->histDefBrush = new QBrush(QColor("#2196F3"));
  this->histDefPen = new QPen(QColor(255, 255, 255));

  this->eqwidget = new EQWidget(audioPlayer, analyzer, this);
  this->eqwidget->hide();
  this->eqwidget->setAntialiased(true);
  this->eqwidget->setShape(AREA);
  this->eqwidget->setBrush(*eqDefBrush);
  this->eqwidget->setPen(*eqDefPen);

  // create histogramm
  this->histogramm =
      new SoundHistogramm(*histDefPen, audioPlayer, audioData, this);
  this->histogramm->hide();
  histogramm->setAntialiased(true);
  this->histogramm->setBrush(*histDefBrush);

  // add widgets to  window
  this->ui->centralGrid->addWidget(histogramm, 2, 0, 1, 2);
  this->ui->centralGrid->addWidget(eqwidget, 1, 0, 1, 2);

  // create indicators
  createIndicators();

  // create timer to update
  this->updator = new QTimer();
  updator->setInterval(20);
  connect(updator, SIGNAL(timeout()), this, SLOT(gameUpdate()));
}

void GameDialog::createIndicators() {
  this->indicatorStyle = QString("border-color: rgba(0, 0, 0,0);\n"
                                 "border-style: inset;\n"
                                 "border-width: 10px;\n"
                                 "color: rgb(255,255,255);\n"
                                 "background-color: ");
  this->indicators = new Indicator *[4];
  indicators[0] = new Indicator(0, indicatorStyle, ui->indicator1, this);
  indicators[1] = new Indicator(1, indicatorStyle, ui->indicator2, this);
  indicators[2] = new Indicator(2, indicatorStyle, ui->indicator3, this);
  indicators[3] = new Indicator(3, indicatorStyle, ui->indicator4, this);

  indicators[0]->setPeriod(1000);
  indicators[1]->setPeriod(1000);
  indicators[2]->setPeriod(1000);
  indicators[3]->setPeriod(1000);
}

GameDialog::GameDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;
  ui->setupUi(this);
  {
    ui->label->hide();
    ui->label_2->hide();
    ui->label_4->hide();
    ui->indicator1->hide();
    ui->indicator2->hide();
    ui->indicator3->hide();
    ui->indicator4->hide();
    ui->songNameLbl->hide();
    ui->stopBtn->hide();
  }
  init();
  start();
  {
    ui->label->show();
    ui->label_2->show();
    ui->label_4->show();
    eqwidget->show();
    histogramm->show();
    ui->songNameLbl->show();
    ui->stopBtn->show();
  }
}

GameDialog::~GameDialog() {
  this->updator->stop();

  audioPlayer->stop();
  delete ui;

  // delete widgets
  delete audioPlayer;
  delete eqwidget;
  delete histogramm;
  delete audioData;

  // delete brushes ad pens
  delete histDefBrush;
  delete histDefPen;

  // delete indicators
  for (int i = 0; i < 4; i++) {
    delete indicators[i];
  }
  delete[] indicators;

  delete eqDefBrush;
  delete eqGoodBrush;
  delete eqBadBrush;
  delete eqDefPen;
  delete updator;
}

void GameDialog::gameUpdate() {
  for (int i = 0; i < 1; i++) {
    indicators[i]->update();
  }
}

void GameDialog::start() {

  QMessageBox mBox;
  mBox.setText("When you will be ready, press ok");
  mBox.exec();
  this->closeGame = false;
  this->eqwidget->start();
  this->histogramm->start();
  this->audioPlayer->play();
  this->updator->start();
}

void GameDialog::reject() {
  if (closeGame)
    QDialog::reject();
}

void GameDialog::on_stopBtn_clicked() {
  closeGame = true;
  this->accept();
}

void GameDialog::indicatorEnd(Indicator *ind) {
  cout << ind->getId() << "was ended" << endl;
  ind->setPeriod(500 + rand() % 3000);
}
