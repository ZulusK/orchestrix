#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <Controller.h>
#include <EQWidget.h>
#include <Game.h>
#include <Indicator.h>
#include <QBrush>
#include <QDialog>
#include <QPen>
#include <QStringList>
#include <QTimer>
#include <QVector>
#include <SoundHistogramm.h>
#include <User.h>

enum { COUNT_OF_INDICATORS = 4 };
class Indicator;

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog {
  Q_OBJECT
private:
  void setup();
  void start();
  void init();
  void addWords();
  void updateInput();
  void reject();
  void createIndicators();
  bool initIndicator(QVector<Indicator *> freeIndicators,
                     unsigned long shootPos, unsigned long currPos);
  void indicatorEnded(Indicator *ind);
  QVector<Indicator *> getFreeIndicators();
  QString loadSound();

public:
  explicit GameDialog(Game *game, QWidget *parent = 0);
  ~GameDialog();

private slots:
  void on_stopBtn_clicked();
  void updateGame();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  // lists of game messages
  QStringList badWord;
  QStringList goodWord;

  bool closeGame;
  // last processed spectrum position
  unsigned long lastProcessedSpectrum;
  // time of last updating
  long lastUpdate;

  Ui::GameDialog *ui;
  Game *environment;
  // widgets
  EQWidget *eqwidget;
  SoundHistogramm *histogramm;
  // sound player
  AudioPlayer *audioPlayer;
  // sound data
  AudioData *audioData;
  // sound analyzer
  SpectrumAnalyzer *analyzer;

  // array of indicators
  Indicator **indicators;

  // custom brushes and pens
  // for equalizer
  QPen *eqDefPen;
  QBrush *histDefBrush;
  // for histogramm
  QPen *histDefPen;
  QBrush *eqDefBrush;
  QBrush *eqGoodBrush;
  QBrush *eqBadBrush;

  // timer to update game
  QTimer *updator;

  // style of indicators
  QString indicatorStyle;

  // controller orchestriX
  Controller *controller;
};

#endif // GAMEDIALOG_H
