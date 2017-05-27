#include "EQWidget.h"
#include "ui_EQWidget.h"
#include <QDebug>
#include <QLineF>
#include <QPainter>
#include <QPainterPath>
#include <Spectrum.h>
#include <iostream>
using namespace std;

double difference(clock_t clock1, clock_t clock2) {
  double diffticks = clock1 - clock2;
  double diffms = (diffticks) / (CLOCKS_PER_SEC);
  if (diffms < 0)
    return 0;
  else
    return diffms;
}

QPointF **getPointsArray(int count) {
  auto points = new QPointF *[count];
  for (int i = 0; i < count; i++) {
    points[i] = new QPointF(0, 0);
  }
  return points;
}

EQWidget::EQWidget(AudioPlayer *player, SpectrumAnalyzer *analyzer,
                   QWidget *parent)
    : QWidget(parent), ui(new Ui::EQWidget) {
  ui->setupUi(this);
  // copy references
  this->player = player;
  this->analyzer = analyzer;
  this->spectrumPos = 0;
  this->barsCount = analyzer->getBars();

  // init timer
  this->timer = new QTimer();
  this->sleepTime = (long)(analyzer->getTimeBound() * 1000*0.4);
  this->timer->setSingleShot(true);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateBars()));
  this->lastUpdateTime = 0;
  this->isPaused = true;

  // create graphics variables
  this->bars = getPointsArray(barsCount);
  this->barType = LINE;
  this->antialiased = false;
  this->pen.setColor(Qt::white);
  this->brush.setColor(Qt::white);
}

EQWidget::~EQWidget() {
  this->timer->stop();
  delete this->timer;
  for (int i = 0; i < barsCount; i++) {
    delete bars[i];
  }
  delete bars;
  delete ui;
}

void EQWidget::updateSpectrumPos() {
  this->spectrumPos = player->getTime() / 1000.0 * analyzer->getFrequency() /
                      analyzer->getElementsInChunk();
}

void EQWidget::timerLoopInit() {
  auto currTimeDiff = sleepTime - difference(clock(), this->lastUpdateTime);
  if (currTimeDiff > 0) {
    timer->setInterval(currTimeDiff);
  } else {
    timer->setInterval(sleepTime);
  }
  this->lastUpdateTime = clock();
  timer->start();
}

void EQWidget::updateBars() {
  if (!isPaused) {
    if (!analyzer->isShoot(spectrumPos)) {
      setBrush(QBrush(QColor(0, 97, 255), Qt::Dense6Pattern));
    } else {
      setBrush(QBrush(QColor(255, 10, 0), Qt::Dense6Pattern));
    }
    auto oldPos = this->spectrumPos;
    updateSpectrumPos();
    // check, is player pos was setting
    if (oldPos != this->spectrumPos) {
      // get new spectrums
      auto valuesNew = analyzer->getSpectrums(spectrumPos);
      // get bar width
      auto barWidth = this->width() / (float)barsCount;
      // update points array
      for (int i = 0; i < barsCount; i++) {
        this->bars[i]->setX(barWidth * (i + 0.5));
        this->bars[i]->setY((1 - valuesNew[i]) * height());
      }
      // update view
      update();
    }
    timerLoopInit();
  }
}

void EQWidget::paintEvent(QPaintEvent *event) {

  QPainter painter(this);
  painter.setBrush(this->brush);
  painter.setPen(this->pen);
  painter.setRenderHint(QPainter::Antialiasing, antialiased);

  switch (this->barType) {
  case RECT:
    drawRectBars(painter);
    break;
  case AREA:
    drawAreaBars(painter);
    break;
  case LINE:
  default:
    drawLineBars(painter);
    break;
  }
}

void EQWidget::drawRectBars(QPainter &painter) {
  auto barWidth = this->width() / (float)barsCount;
  for (int i = 0; i < barsCount; i++) {
    painter.drawRect(i * barWidth, height() - bars[i]->y(), barWidth,
                     bars[i]->y());
  }
}

void EQWidget::drawLineBars(QPainter &painter) {
  painter.drawLine(QPointF(0, height()), *this->bars[0]);
  for (int i = 1; i < barsCount; i++) {
    painter.drawLine(*bars[i - 1], *bars[i]);
  }
  painter.drawLine(*this->bars[this->barsCount - 1],
                   QPointF(width(), height()));
  painter.drawLine(QPointF(0, height()), QPointF(width(), height()));
}

void EQWidget::drawAreaBars(QPainter &painter) {
  QPainterPath path;
  path.moveTo(0, height());
  for (int i = 0; i < barsCount; i++) {
    path.lineTo(*bars[i]);
  }
  path.lineTo(QPointF(width(), height()));
  path.lineTo(0, height());
  painter.drawPath(path);
}

QSize EQWidget::minimumSizeHint() const { return QSize(100, 100); }

QSize EQWidget::sizeHint() const { return QSize(200, 200); }

void EQWidget::start() {
  if (isPaused) {
    isPaused = false;
    lastUpdateTime = 0;
    timerLoopInit();
  }
}

void EQWidget::pause() { isPaused = true; }

void EQWidget::setShape(EQShape shape) { this->barType = shape; }

void EQWidget::setPen(const QPen &pen) { this->pen = pen; }

void EQWidget::setBrush(const QBrush &brush) { this->brush = brush; }

void EQWidget::setAntialiased(bool antialiased) {
  this->antialiased = antialiased;
}

EQShape EQWidget::getEQShape() { return this->barType; }

void EQWidget::updateEQ() { update(); }

unsigned long EQWidget::getSpectrumPos() { return this->spectrumPos; }
