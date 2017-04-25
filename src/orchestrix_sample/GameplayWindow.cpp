#include "GameplayWindow.h"
#include "ui_GameplayWindow.h"
#include <AudioManagement/AudioData.h>
#include <AudioManagement/AudioManager.h>
#include <AudioManagement/AudioPlayer.h>
#include <AudioManagement/OpenAL.h>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <SpectrumManagement/Spectrum.h>
#include <SpectrumManagement/SpectrumAnalyzer.h>
#include <string>
#include <thread>

using namespace QtCharts;
using namespace std;

GameplayWindow::GameplayWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameplayWindow) {
  ui->setupUi(this);
  initBars();
  ui->mus2->click();
}

GameplayWindow::~GameplayWindow() { delete ui; }

void GameplayWindow::initBars() {
  QBarSet *set0 = new QBarSet(NULL);
  for (int i = 0; i < 20; i++) {
    *set0 << i;
  }
  QBarSeries *series = new QBarSeries();
  series->append(set0);
  chart = new QChart();

  chart->addSeries(series);
  chart->setAnimationOptions(QChart::SeriesAnimations);
  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  this->setCentralWidget(chartView);
}

void GameplayWindow::updateBars(Spectrum *spectrum) {
  int max = 100;
  chart->removeAllSeries();
  QBarSet *set0 = new QBarSet(NULL);
  const float *s = spectrum->getSpectrums();
  for (int i = 0; i < spectrum->getLength(); i++) {
      cout<<s[i]<<endl;
    *set0 << max * s[i];
      *set0<<i;
  }
  QBarSeries *series = new QBarSeries();
  series->append(set0);
  chart->addSeries(series);
  chart->update(0,0,100,100);
}

void GameplayWindow::updateEQ(SpectrumAnalyzer *analyzer) {
  for (size_t i = 0; i < analyzer->getBars(); i++) {
    updateBars(analyzer->getSpectrums()[0]);
    cout<<"try to update "<<analyzer->getTimeBound()<<endl;
    std::this_thread::sleep_for(
        std::chrono::milliseconds((int)(analyzer->getTimeBound()*1000)));
  }
}

void GameplayWindow::playSound(string name) {
  AudioData *sound1 = AudioData::load(name);
  AudioManager *manager = AudioManager::init(1, 8);
  AudioPlayer *player1 = new AudioPlayer(manager, sound1, 1);
  SpectrumAnalyzer *analyzer = new SpectrumAnalyzer(sound1, 1024, 20);
  cout << player1->toString() << endl;
  std::thread *t1 = player1->play();
  std::thread *t2 = new std::thread(&GameplayWindow::updateEQ, this, analyzer);
  t1->join();
  t2->join();
  delete t1;
  delete player1;
  delete manager;
  delete sound1;
}

void GameplayWindow::on_mus2_clicked() {
  std::thread *t = new std::thread(&GameplayWindow::playSound, this,
                                   "../audio/res/21pilots.wav");
}
