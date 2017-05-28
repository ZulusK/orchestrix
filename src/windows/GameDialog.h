#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <EQWidget.h>
#include <Game.h>
#include <Indicator.h>
#include <QBrush>
#include <QDialog>
#include <QPen>
#include <QStringList>
#include <QTimer>
#include <SoundHistogramm.h>
#include <User.h>
#include <Controller.h>
class Indicator;

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog {
  Q_OBJECT
private:
  bool addIndicator(unsigned long pos, unsigned long curr);
  QString loadSound();
  void init();
  void start();
  void reject();
  void createIndicators();
  void addWords();
  void updateInput();

public:
  explicit GameDialog(Game *game, QWidget *parent = 0);
  ~GameDialog();
  void indicatorEnd(Indicator *ind);

private slots:
  void on_stopBtn_clicked();
  void gameUpdate();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  int brushUsedIteration;
  QStringList badWord;
  QStringList goodWord;
  bool closeGame;
  unsigned long lastAddedShoot;
  long lastUpdate;
  Ui::GameDialog *ui;
  Game *environment;
  EQWidget *eqwidget;
  SoundHistogramm *histogramm;
  AudioPlayer *audioPlayer;
  AudioData *audioData;
  SpectrumAnalyzer *analyzer;

  Indicator **indicators;

  QBrush *histDefBrush;
  QPen *histDefPen;

  QPen *eqDefPen;
  QBrush *eqDefBrush;
  QBrush *eqGoodBrush;
  QBrush *eqBadBrush;
  QTimer *updator;

  QString indicatorStyle;

  Controller * controller;
};

#endif // GAMEDIALOG_H
