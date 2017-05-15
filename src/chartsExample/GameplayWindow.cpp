#include "GameplayWindow.h"
#include "ui_GameplayWindow.h"
#include <QTimer>
#include <stdlib.h>
QT_CHARTS_USE_NAMESPACE
GameplayWindow::GameplayWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GameplayWindow) {
  ui->setupUi(this);
  currentSpectr = 0;
  processSpectrum();
  initEQ();
}

GameplayWindow::~GameplayWindow() {
  delete player;
  delete manager;
  delete ui;
}

void GameplayWindow::updateEQ() {
  int count = analyzer->getBars();
  int size = analyzer->getSpectrums().size();
  if (currentSpectr < size) {
    Spectrum *s = analyzer->getSpectrums().at(currentSpectr);
    const float *bars = s->getSpectrums();
    currentSpectr++;
    updateChart(bars, count);
    this->repaint();
//    cout<<currentSpectr<<"/"<<size<<endl;
  }
}

void GameplayWindow::updateChart(const float *arr, int count) {
  int max = 100;
  equalizer->removeAllSeries();
  QBarSeries *series = new QBarSeries();
  QBarSet *set = new QBarSet(NULL);
//  *set << max;
  series->append(set);
  for (int i = 0; i < count; i++) {
    set = new QBarSet(NULL);
    *set << (arr[i] * max);
    series->append(set);
  }
  equalizer->addSeries(series);
}

void GameplayWindow::initEQ() {
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateEQ()));
  timer->start(analyzer->getTimeBound());
  srand(time(NULL));
  equalizer = new QChart();

  updateEQ();
  equalizer->legend()->setVisible(false);

  QChartView *chartView = new QChartView(equalizer);
  chartView->setRenderHint(QPainter::Antialiasing);
  ui->mainLayout->addWidget(chartView);
  player->play();
}

void GameplayWindow::processSpectrum() {
  AudioData *data = AudioData::load("../audio/res/ppl.wav");
  analyzer = new SpectrumAnalyzer(data, SAMPLE_1024, 60);
  manager = AudioManager::init();
  player = new AudioPlayer(manager, data, 1);
  std::cout << analyzer->getSpectrums().size() << endl;
  std::cout << analyzer->getTimeBound() << endl;
}
