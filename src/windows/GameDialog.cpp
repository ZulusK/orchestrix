#include "GameDialog.h"
#include "ui_GameDialog.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
using namespace std;

#define TIME_INTERVAL 1500

GameDialog::GameDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();

  // copy ref
  this->environment = game;
  // check, is user present
  if (environment->getUser() == NULL) {
    environment->addUser(new User("No name"));
  }
  environment->getUser()->setScore(0);
  this->eqwidget=NULL;
  this->histogramm=NULL;
  this->setup();
}

void GameDialog::setup() {
  // set labels text
  // and hide them

  ui->playerNameLbl->setText(environment->getUser()->getName());
  ui->playerNameLbl->hide();

  ui->currentScoreLbl->hide();
  ui->currentScoreLbl->setText("");

  ui->totalScoreLbl->hide();
  ui->totalScoreLbl->setText("0");

  ui->messageLbl->hide();
  ui->messageLbl->setText("Start new game");

  ui->scoreLbl->hide();
  ui->songNameLbl->hide();

  ui->stopBtn->hide();
  ui->indicator0->hide();
  ui->indicator1->hide();
  ui->indicator2->hide();
  ui->indicator3->hide();

  // initialize player, analyzer and etc.
  init();
  // add words to lists
  addWords();
  // show labels

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
  ui->indicator0->show();
  ui->indicator1->show();
  ui->indicator2->show();
  ui->indicator3->show();

  lastProcessedSpectrum = 0;
  colorChangetCounter = 0;
  // start executing game
  start();
}

QString GameDialog::loadSound() {
  // get user choose
  QString soundPath = QFileDialog::getOpenFileName(
      this, QString::fromUtf8("Choose your sound file"), QDir::homePath(),
      "Sounds (*.wav);;");
  // if user doesn't select any sound
  // than use default sound
  if (soundPath.length() == 0) {
    soundPath = environment->getHomepath() + "res/we will rock u.wav";
  }
  // load sound
  this->audioData = AudioData::load(soundPath.toStdString());
  // if cannot load any sound, then exit
  if (!audioData) {
    qDebug() << "Cannot load sound";
    closeGame = true;
    this->reject();
    return "";
  }
  // create sound player
  this->audioPlayer =
      new AudioPlayer(environment->getAudioManager(), audioData, 2);
  // create analyzer
  this->analyzer = new SpectrumAnalyzer(audioData, SAMPLE_1024, 50);
  // add sound name to user info
  this->environment->getUser()->setSoundName(soundPath.split("/").last());
  return soundPath;
}

void GameDialog::addWords() {
    this->badWord << "Try again";
      this->badWord << "Sad";
      this->badWord << "Bad";
      this->badWord << "Are you playing?";
      this->badWord << "My sister plays better";
      this->badWord << "Legeza would be ashamed";
      this->badWord << "Did you get the rules?";
      this->badWord << "*Sad cat picture*";
      this->badWord << "Close the game, please";
      this->badWord << "Stop torturing me and yourself";
      this->badWord << "Better go play outside";
      this->badWord << "This is not your thing, man";
      this->badWord << "You chicken?";
      this->badWord << "Sloppy";
      this->badWord << "Try harder";
      this->badWord << "Stop embarrassing yourself";
      this->badWord << "OUCH";
      this->badWord << "Edward Scissorhands, is that you?";
      this->badWord << "Go kill yourself";


      this->goodWord << "Crazy";
      this->goodWord << "Wooo";
      this->goodWord << "Amazing";
      this->goodWord << "Like Sikorskiy";
      this->goodWord << "May be you are God?";
      this->goodWord << "I like it";
      this->goodWord << "Continue!";
      this->goodWord << "=)";
      this->goodWord << ")))))0))";
      this->goodWord << "Fatality";
      this->goodWord << "Combo";
      this->goodWord << "Ultra kill";
      this->goodWord << "Maestro";
      this->goodWord << "How are you doing this?";
      this->goodWord << "Legeza would be proud";
      this->goodWord << "Prodigy";
      this->goodWord << "OOOOH YEEEAH";
      this->goodWord << "Fantastic!";
      this->goodWord << "";
}

void GameDialog::init() {
  // init randomizer
  this->controller = new Controller();
  // if cannot create controller - exit
  if (!controller->isConnected()) {
    qDebug() << "Oops, there is some problem with controller connection";
    this->closeGame = true;
    this->reject();
  }

  srand(time(NULL));
  // load sound
  loadSound();
  // load standart sounds to game's environment
//  environment->loadSound(environment->getHomepath() +
//                         "res/sound effects/bad.wav");
//  environment->loadSound(environment->getHomepath() +
//                         "res/sound effects/good.wav");

  // create custom brushes and pens
  // for equalizer
  this->eqDefPen = new QPen(QColor("#2196F3"), 10, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin);
  this->eqDefBrush = new QBrush(QColor(33, 150, 243), Qt::Dense6Pattern);
  this->eqBadBrush = new QBrush(QColor(255, 20, 0), Qt::Dense6Pattern);
  this->eqGoodBrush = new QBrush(QColor(0, 255, 20), Qt::Dense6Pattern);

  // for histogramm
  this->histDefBrush = new QBrush(QColor("#2196F3"));
  this->histDefPen = new QPen(QColor(255,255,255));

  // create equalizer
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

  // create timer to update
  this->updator = new QTimer();
  updator->setInterval(40);
  // connect slot to timer's signal
  connect(updator, SIGNAL(timeout()), this, SLOT(updateGame()));

  // initilize indicators
  createIndicators();
}

void GameDialog::createIndicators() {
  // add custom style to them
  this->indicatorStyle =
      QString("border-color: rgba(0, 0, 0,0);\n"
              "border-style: inset;\n"
              "border-width: 4px;\n"
              "color: rgb(255,255,255);\n"
              //                                 "border-color: white;\n"
              "background-color: ");

  // add custom style to message label
  this->messageStyle = QString("border-color: rgba(0, 0, 0,0);\n");
  ui->messageLbl->setStyleSheet(messageStyle + "color:white;");
  // create 4 indicators
  this->indicators = new Indicator *[COUNT_OF_INDICATORS];
  indicators[0] =
      new Indicator(0, indicatorStyle, ui->indicator0, controller, this);
  indicators[1] =
      new Indicator(1, indicatorStyle, ui->indicator1, controller, this);
  indicators[2] =
      new Indicator(2, indicatorStyle, ui->indicator2, controller, this);
  indicators[3] =
      new Indicator(3, indicatorStyle, ui->indicator3, controller, this);
}

GameDialog::~GameDialog() {
  // delete timer
  this->updator->stop();
  delete updator;

  // delete indicators
  for (int i = 0; i < 4; i++) {
    delete indicators[i];
    controller->turnOffLed(i);
  }
  delete[] indicators;

  // stop the player
  audioPlayer->stop();

  // delete controller
  delete controller;

  // delete ui
  delete ui;

  // delete widgets
  delete audioPlayer;
  delete eqwidget;
  delete histogramm;
  delete audioData;

  // delete brushes ad pens
  delete histDefBrush;
  delete histDefPen;
  delete eqDefBrush;
  delete eqGoodBrush;
  delete eqBadBrush;
  delete eqDefPen;
}

void GameDialog::start() {
  // create message box to ask user
  // when he will be ready
  QMessageBox mBox;
  mBox.setText("When you will be ready, press ok");
  mBox.exec();

  this->closeGame = false;
  // start updating widgets
  this->eqwidget->start();
  this->histogramm->start();

  // start playing sound
  this->audioPlayer->play();

  // start updating timer
  this->updator->start();
}

QVector<Indicator *> GameDialog::getFreeIndicators() {
  QVector<Indicator *> freeIndicators;
  Indicator *fi[COUNT_OF_INDICATORS];
  // clear indicators
  for (int i = 0; i < COUNT_OF_INDICATORS; i++) {
    fi[i] = NULL;
  }
  // randomize sequence of inicators
  for (int i = 0; i < COUNT_OF_INDICATORS; i++) {
    if (!indicators[i]->isBusy()) {
      int j = rand() % 4;
      while (1) {
        if (fi[j % 4] == NULL) {
          fi[j % 4] = indicators[i];
          break;
        } else {
          j++;
        }
      }
    }
  }
  // add indicators to vector
  for (int i = 0; i < COUNT_OF_INDICATORS; i++) {
    if (fi[i] != NULL) {
      freeIndicators.push_back(fi[i]);
    }
  }
  return freeIndicators;
}

bool GameDialog::initIndicator(QVector<Indicator *> freeIndicators,
                               unsigned long shootPos, unsigned long currPos) {
  // get first free indicator
  Indicator *indicator = freeIndicators[0];
  freeIndicators.erase(freeIndicators.begin());

  // set period in indicator
  long time = (shootPos - currPos) * analyzer->getTimeBound();
  indicator->setPeriod(time);
  return freeIndicators.size() == 0;
}

void GameDialog::updateGame() {
  if (closeGame) {
    return;
  }
  // if sound was ended, close game
  if (audioPlayer->isStopped()) {
    ui->stopBtn->click();
  }

  // update user input
  updateInput();

  // update each indicator
  for (int i = 0; i < 4; i++) {
    // if indicator ended, then process this event
    if (indicators[i]->update()) {
      this->indicatorEnded(indicators[i], false);
    }
  }

  // get free indicators
  auto freeIndicators = getFreeIndicators();
  // if there is free
  if (freeIndicators.size() != 0) {

    // get current spectrum from equalizer
    auto currSpectrum = eqwidget->getSpectrumPos();
    // if last processed spectrum's number is late,
    // update it before continue
    auto shift=TIME_INTERVAL/analyzer->getTimeBound()/10;
    if (lastProcessedSpectrum < currSpectrum+shift) {
      lastProcessedSpectrum = currSpectrum+shift;
    }

    // get next left bound of spectrums
    unsigned long bound =
        currSpectrum + (TIME_INTERVAL) / analyzer->getTimeBound();

    // search to shoot
    for (; lastProcessedSpectrum < bound; lastProcessedSpectrum++) {
      // if find shoot
      if (analyzer->isShoot(lastProcessedSpectrum)) {
        // if the free indicators have run out
        if (initIndicator(freeIndicators, lastProcessedSpectrum,
                          currSpectrum)) {
          return;
        }
      } else {
        // add shift to pointer
        lastProcessedSpectrum += analyzer->getSpace() / 2;
      }
    }
  }
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
  if (controller->isConnected()) {
    bool *input = controller->getInput();
    for (int i = 0; i < COUNT_OF_INDICATORS; i++) {
      // if user influenced the sensor
      if (input[i]) {
        // if indicator is used, then input is correct
        indicatorEnded(indicators[i], indicators[i]->isBusy());
      }
    }
    delete input;
  }
}

void GameDialog::indicatorEnded(Indicator *ind, bool success) {
  // calculate negative bonus
  int bonus = 100 * ind->getTimePeriod() / (float)TIME_INTERVAL;
  if (!success) {
    bonus *= -1;
  }else{
      bonus*=10;
  }
  // add bonus to user
  environment->getUser()->addToScore(bonus);

  if (success) {
    //    environment->play("good.wav");
    // set color of eq
    changeBrush(eqGoodBrush, 15);
    ui->messageLbl->setText(badWord[rand() % badWord.size()]);
    ui->messageLbl->setStyleSheet(messageStyle + "color:rgb(0,255,20)");
    // update text
    ui->currentScoreLbl->setText("+" + QString::number(bonus));
  } else {
    //    environment->play("bad.wav");
    // set color of eq
    changeBrush(eqBadBrush, 15);
    ui->messageLbl->setText(goodWord[rand() % goodWord.size()]);
    ui->messageLbl->setStyleSheet(messageStyle + "color:rgb(255,20,0)");
    // update text
    ui->currentScoreLbl->setText(QString::number(bonus));
  }

  ind->setPeriod(-1);
}

void GameDialog::changeBrush(QBrush *brush, int count) {
  if (colorChangetCounter > 0) {

  } else {
    eqwidget->setBrush(*brush);
    this->colorChangetCounter = count;
  }
}

void GameDialog::paintEvent(QPaintEvent *event) {
  ui->totalScoreLbl->setText(
      QString::number(environment->getUser()->getScore()));
  colorChangetCounter--;
  if(eqwidget!=NULL)
  changeBrush(eqDefBrush, 0);
}

void GameDialog::on_indicator0_clicked() {
  indicatorEnded(indicators[0], indicators[0]->isBusy());
}

void GameDialog::on_indicator1_clicked() {
  indicatorEnded(indicators[1], indicators[1]->isBusy());
}

void GameDialog::on_indicator2_clicked() {
  indicatorEnded(indicators[2], indicators[2]->isBusy());
}

void GameDialog::on_indicator3_clicked() {
  indicatorEnded(indicators[3], indicators[3]->isBusy());
}
