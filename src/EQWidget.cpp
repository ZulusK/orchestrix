#include "EQWidget.h"
#include "ui_EQWidget.h"
#include <QDebug>
#include <QPainter>
#include <Spectrum.h>
EQWidget::EQWidget(AudioPlayer *player, SpectrumAnalyzer *analyzer,
                   QWidget *parent)
    : QWidget(parent), ui(new Ui::EQWidget) {
  ui->setupUi(this);
  this->player = player;
  this->barsCount = analyzer->getBars();
  this->analyzer = analyzer;
  updateSpectrumPos();
}

EQWidget::~EQWidget() { delete ui; }
QSize EQWidget::minimumSizeHint() const { return QSize(100, 100); }

void EQWidget::updateSpectrumPos() {
  this->spectrumPos = player->getTime() / 1000 * analyzer->getFrequency() /
                      analyzer->getElementsInChunk();
}

void EQWidget::updateEQ() {
  this->repaint();
  qDebug() << "updated";
}

QSize EQWidget::sizeHint() const { return QSize(200, 200); }

void EQWidget::paintEvent(QPaintEvent * /* event */) {
  double barSize = (this->width() - SPACE_BORDER) / (float)barsCount;
  QPainter painter(this);
  painter.setBrush(QBrush(Qt::blue));
  painter.setPen(QPen(Qt::white, 3));
  painter.setRenderHint(QPainter::Antialiasing, true);
  //  const float *values = analyzer->getSpectrums(spectrumPos);
  for (int i = 0; i < this->barsCount; i++) {
    painter.drawLine(QPoint(SPACE_BORDER + i * barSize, this->height()),
                     QPoint(SPACE_BORDER + (i + 0.5) * barSize, 0));
    painter.drawLine(QPoint(SPACE_BORDER + (i + 0.5) * barSize, 0),
                     QPoint(SPACE_BORDER + (i + 1) * barSize, this->height()));
  }

  painter.setPen(palette().dark().color());
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
