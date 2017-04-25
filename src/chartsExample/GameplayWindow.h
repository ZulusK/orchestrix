#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioPlayer.h>
#include <QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <SpectrumManagement/Spectrum.h>
#include <SpectrumManagement/SpectrumAnalyzer.h>

#define EQ_BARS_COUNT 20
namespace Ui {
class GameplayWindow;
}
QT_CHARTS_USE_NAMESPACE
class GameplayWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit GameplayWindow(QWidget *parent = 0);
  ~GameplayWindow();
private slots:

  void updateEQ();

private:
  int currentSpectr;
  Ui::GameplayWindow *ui;
  SpectrumAnalyzer *analyzer;
  QChart *equalizer;
  AudioManager* manager;
  AudioPlayer * player;
  void processSpectrum();
  void initEQ();
  void updateChart(const float *arr, int count);
};

#endif // GAMEPLAYWINDOW_H
