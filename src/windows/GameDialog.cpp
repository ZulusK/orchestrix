#include "GameDialog.h"
#include "ui_GameDialog.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
using namespace std;

#define TIME_INTERVAL 500
QString GameDialog::loadSound() {
  QString soundPath = QFileDialog::getOpenFileName(
      this, QString::fromUtf8("Choose your sound to play"), QDir::currentPath(),
      "Sounds (*.wav);;");
  if (soundPath.length() == 0) {
    soundPath = "../orchestrix/res/we will rock u.wav";
  }
  // load sound
  this->audioData = AudioData::load(soundPath.toStdString());
  if (!audioData) {
    soundPath = "../orchestrix/res/ppl.wav";
    this->audioData = AudioData::load(soundPath.toStdString());
  }
  // create sound player
  this->audioPlayer =
      new AudioPlayer(environment->getAudioManager(), audioData, 2);

  this->analyzer = new SpectrumAnalyzer(audioData, SAMPLE_1024, 50);
  this->environment->getUser()->setSoundName(soundPath.split("/").constLast());
  return soundPath;
}
void GameDialog::addWords() {
  this->badWord << "Try again";
  this->badWord << "Sad";
  this->badWord << "Bad";
  this->badWord << "Are you playing?";
  this->badWord << "My sister playes better";

  this->goodWord << "Crazy";
  this->badWord << "Wooo";
  this->badWord << "Amazing";
  this->badWord << "Like Sikorskiy";
  this->badWord << "May be you are God?";
  this->badWord << "I like it";
  this->badWord << "Continue!";
  this->badWord << "=)";
  this->badWord << ")))))0))";
}

void GameDialog::init() {

  srand(time(NULL));
  // load sound
  loadSound();
  addWords();
  // load standart sounds
  environment->loadSound("../orchestrix/res/sound effects/bad.wav");
  environment->loadSound("../orchestrix/res/sound effects/good.wav");

  // create equlizer view
  this->eqDefPen = new QPen(QColor("#2196F3"), 10, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin);
  //this->eqDefBrush = new QBrush(QColor("#2196F3"), Qt::Dense6Pattern);
  this->eqDefBrush = new QBrush(QColor(20,255,20), Qt::Dense6Pattern);
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
  // create conroller
  this->controller = new Controller();
  cout<<"controller"<<controller->isConnected()<<endl;
}

void GameDialog::createIndicators() {
  this->indicatorStyle = QString("border-color: rgba(0, 0, 0,0);\n"
                                 "border-style: inset;\n"
                                 "border-width: 4px;\n"
                                 "color: rgb(255,255,255);\n"
                                 "border-color: white;\n"
                                 "background-color: ");
  this->indicators = new Indicator *[4];
  indicators[0] = new Indicator(0, indicatorStyle, ui->indicator1, this);
  indicators[1] = new Indicator(1, indicatorStyle, ui->indicator2, this);
  indicators[2] = new Indicator(2, indicatorStyle, ui->indicator3, this);
  indicators[3] = new Indicator(3, indicatorStyle, ui->indicator4, this);
  lastAddedShoot = 0;
}

GameDialog::GameDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;
  game->addUser(new User("Vasya"));
  ui->setupUi(this);
  {
    ui->playerNameLbl->setText(game->getUser()->getName());
    ui->playerNameLbl->hide();

    ui->currentScoreLbl->hide();
    ui->currentScoreLbl->setText("");

    ui->totalScoreLbl->hide();
    ui->totalScoreLbl->setText("0");

    ui->messageLbl->hide();
    ui->messageLbl->setText("PLAY!!!!!!!!!");

    ui->scoreLbl->hide();
    ui->songNameLbl->hide();

    ui->stopBtn->hide();
    ui->indicator1->hide();
    ui->indicator2->hide();
    ui->indicator3->hide();
    ui->indicator4->hide();
  }
  init();
  start();
  {
    eqwidget->show();
    histogramm->show();
    ui->playerNameLbl->show();
    ui->currentScoreLbl->show();
    ui->totalScoreLbl->show();
    ui->messageLbl->show();
    ui->scoreLbl->show();
    ui->songNameLbl->setText(environment->getUser()->getSoundName());
    ui->songNameLbl->show();
    ui->stopBtn->show();
    ui->indicator1->show();
    ui->indicator2->show();
    ui->indicator3->show();
    ui->indicator4->show();
  }
}

GameDialog::~GameDialog() {
  this->updator->stop();
  delete updator;

  // delete indicators
  for (int i = 0; i < 4; i++) {
    delete indicators[i];
  }
  delete[] indicators;

  audioPlayer->stop();
  delete controller;
  // delete widgets
  delete audioPlayer;
  delete eqwidget;
  delete histogramm;
  delete audioData;
  // delete brushes ad pens
  delete histDefBrush;
  delete histDefPen;
  delete ui;
  delete eqDefBrush;
  delete eqGoodBrush;
  delete eqBadBrush;
  delete eqDefPen;
}

bool GameDialog::addIndicator(unsigned long pos, unsigned long curr) {

  bool freeInd[4];
  for (int i = 0; i < 4; i++) {
    freeInd[i] = true;
  }
  // find random free indicator
  while (true) {
    int id = rand() % 4;
    if (indicators[id]->isBusy()) {
      freeInd[id] = false;
    } else {
      auto timeBound = (pos - curr) * analyzer->getTimeBound();
      indicators[id]->setCurPos(pos);
      indicators[id]->setPeriod(timeBound);
      return true;
    }
    for (int i = 0; i < 4; i++) {
      if (freeInd[i]) {
        continue;
      }
    }
    break;
  }
  return false;
}

void GameDialog::gameUpdate() {
  if (closeGame) {
    return;
  }
  if (audioPlayer->isStopped()) {
    ui->stopBtn->click();
  }
  for (int i = 0; i < 4; i++) {
    indicators[i]->update();
  }

  auto currSpectrum = (audioPlayer->getTime()) / analyzer->getTimeBound();
  if (lastAddedShoot < currSpectrum) {
    lastAddedShoot = currSpectrum;
  }
  long bound = lastAddedShoot + (TIME_INTERVAL) / analyzer->getTimeBound();
  cout << "start " << lastAddedShoot << endl;
  cout << "bound " << bound << endl << endl;
  for (; lastAddedShoot < bound; lastAddedShoot++) {
    // if find shoot
    if (analyzer->isShoot(lastAddedShoot)) {
      cout << "next shoot is :" << lastAddedShoot << endl;
      if (!addIndicator(lastAddedShoot, currSpectrum)) {
        // if all indicators is busy
        return;
      } else {
        lastAddedShoot += analyzer->getSpace() / 2;
      }
    }
  }
  updateInput();
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

void GameDialog::updateInput() {
  auto input = controller->getInput();
  int bonus = 0;
  for (int i = 0; i < 4; i++) {
    if (input[i] != indicators[i]->isBusy()) {
      bonus = -10;
      ui->currentScoreLbl->setText(QString::number(bonus));
      ui->messageLbl->setText("...Miss...");
      if (brushUsedIteration <= 0) {
        eqwidget->setBrush(*eqBadBrush);
        this->brushUsedIteration = 3;
      }
    } else {
      bonus = 100 * indicators[i]->getTimePeriod() / TIME_INTERVAL;
      ui->currentScoreLbl->setText("+" + QString::number(bonus));
      ui->messageLbl->setText(goodWord.at(rand() % goodWord.size()));
      eqwidget->setBrush(*eqGoodBrush);
      this->brushUsedIteration = 5;
      indicators[i]->setPeriod(-1);
    }
    environment->getUser()->addToScore(bonus);
  }
  delete[] input;
}

void GameDialog::indicatorEnd(Indicator *ind) {
  int bonus = -100 * ind->getTimePeriod() / TIME_INTERVAL;
  environment->getUser()->addToScore(bonus);
  ui->currentScoreLbl->setText(QString::number(bonus));
  ui->messageLbl->setText(badWord.at(rand() % badWord.size()));
  if (brushUsedIteration <= 0) {
    eqwidget->setBrush(*eqBadBrush);
    this->brushUsedIteration = 3;
  }
  ind->setPeriod(-1);
}

void GameDialog::paintEvent(QPaintEvent *event) {
  if (brushUsedIteration > 0) {
    brushUsedIteration--;
  } else {
    eqwidget->setBrush(*eqDefBrush);
  }
  ui->totalScoreLbl->setText(
      QString::number(environment->getUser()->getScore()));
}
