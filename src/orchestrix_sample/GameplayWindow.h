#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <QMainWindow>
#include <SpectrumManagement/Spectrum.h>
#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>

namespace Ui {
class GameplayWindow;
}

class GameplayWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit GameplayWindow(QWidget *parent = 0);
  ~GameplayWindow();

private slots:
  void on_mus2_clicked();

private:
  Ui::GameplayWindow *ui;
  void updateBars(Spectrum *spec);
  void initBars();
  void playSound(string name);
  void updateEQ(SpectrumAnalyzer *analyzer);
  QtCharts::QChart *chart;
};

#endif // GAMEPLAYWINDOW_H
