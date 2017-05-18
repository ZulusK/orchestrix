#include "GameDialog.h"
#include "ui_GameDialog.h"
#include <QDir>
#include <QFileDialog>
#include <QTimer>
GameDialog::GameDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;

  this->audioData = AudioData::load(
      QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
                                   QDir::currentPath(), "Images (*.wav);;")
          .toStdString());
  this->manager = AudioManager::init();
  this->audioPlayer = new AudioPlayer(manager, audioData, 1);
  this->analyzer = new SpectrumAnalyzer(audioData, SAMPLE_2048, 30);

  this->eqwidget = new EQWidget(audioPlayer, analyzer, this);
  ui->centralGrid->addWidget(eqwidget, 1, 0, 1, 2);
  QTimer::singleShot(analyzer->getTimeBound() * 1000, this,
                     SLOT(updateCaption()));
}

GameDialog::~GameDialog() {
  delete audioPlayer;
  delete audioData;
  delete ui;
  //  delete eqwidget;
}

void GameDialog::updateEQ() {
  eqwidget->updateEQ();
  QTimer::singleShot(analyzer->getTimeBound() * 1000, this,
                     SLOT(updateCaption()));
}
