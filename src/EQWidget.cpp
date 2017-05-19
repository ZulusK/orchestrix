#include "EQWidget.h"
#include "ui_EQWidget.h"
#include <QDebug>
#include <QLineF>
#include <QPainter>
#include <QPainterPath>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <Spectrum.h>
#include <iostream>
using namespace std;

QVariant lineInterpolator(const QLineF &start, const QLineF &end,
                          qreal progress) {
  qreal dy = start.y1() + (end.y1() - start.y1()) * progress;
  return QLineF(start.x1(), dy, start.x2(), 0);
}

QPropertyAnimation **EQWidget::createAnimators(int count) {
  auto animators = new QPropertyAnimation *[count];
  for (int i = 0; i < count; i++) {
    animators[i] = new QPropertyAnimation(this, "barHeight");
  }
  return animators;
}

EQWidget::EQWidget(AudioPlayer *player, SpectrumAnalyzer *analyzer,
                   QWidget *parent)
    : QWidget(parent), ui(new Ui::EQWidget) {
  qRegisterAnimationInterpolator<QLineF>(lineInterpolator);
  ui->setupUi(this);
  this->player = player;
  this->analyzer = analyzer;
  this->updateTimer = new QTimer();
  this->spectrumPos = 0;
  this->barsCount = analyzer->getBars();
  this->animators = createAnimators(this->barsCount);
  connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateBars()));
  connect(this, SIGNAL(eqChanged()), parent, SLOT(update()));
  this->sleepTime = (long)analyzer->getTimeBound() * 1000;
  updateTimer->setInterval(sleepTime);
  updateTimer->setSingleShot(true);
  updateTimer->start();
  lastUpdate = clock();
}

double getSleepTime(clock_t clock1, clock_t clock2) {
  double diffticks = clock1 - clock2;
  double diffms = (diffticks) / (CLOCKS_PER_SEC);
  if (diffms < 0)
    return 0;
  else
    return diffms;
}

EQWidget::~EQWidget() {
  this->updateTimer->stop();
  delete updateTimer;
  for (int i = 0; i < barsCount; i++) {
    delete animators[i];
  }
  delete this->animators;
  delete ui;
}

void EQWidget::updateSpectrumPos() {
  this->spectrumPos = player->getTime() / 1000.0 * analyzer->getFrequency() /
                      analyzer->getElementsInChunk();
}

void EQWidget::updateBars() {

  auto valuesOld = analyzer->getSpectrums(spectrumPos);
  updateSpectrumPos();
  auto valuesNew = analyzer->getSpectrums(spectrumPos);
  this->barsMap.clear();

  double barSize = (this->width()) / (float)barsCount;

  for (int i = 0; i < barsCount; i++) {
    //    QLineF pointOld(barSize * (i + 0.5), (1 - valuesNew[i]) * height(), i,
    //    0);
    QLineF pointOld(barSize * (i + 0.5), 0, i, 0);
    QLineF pointNew(barSize * (i + 0.5), (1 - valuesOld[i]) * height(), i, 0);
    auto anim = animators[i];
    anim->setDuration(1000);
    anim->setStartValue(pointOld);
    anim->setEndValue(pointNew);
    groupAnimation.addAnimation(anim);
  }
  groupAnimation.start();
  cout << groupAnimation.duration() << endl;
  auto T = sleepTime - getSleepTime(clock(), lastUpdate);
  updateTimer->setInterval((T > 0) ? T : 0);
  lastUpdate = clock();
  updateTimer->start();
}

void EQWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setBrush(QBrush(Qt::red));
  painter.setPen(QPen(Qt::white, 2));
  painter.setRenderHint(QPainter::Antialiasing, true);

  for (int i = 1; i < barsCount; i++) {
    painter.setPen(QPen(Qt::white, 2));
    painter.drawLine(barsMap[i - 1], barsMap[i]);
    painter.setPen(QPen(Qt::red, 2));
    painter.drawEllipse(barsMap[i], 4, 4);
  }
  painter.setPen(palette().dark().color());
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void EQWidget::setBar(QLineF &value) {
  this->barsMap[(int)value.p2().x()] = value.p1();
  if ((int)value.p2().x() + 1 == this->barsCount) {
    update();
  }
}

QSize EQWidget::minimumSizeHint() const { return QSize(100, 100); }

QSize EQWidget::sizeHint() const { return QSize(200, 200); }
