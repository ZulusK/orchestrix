#include "EQWidget.h"
#include "ui_EQWidget.h"
#include <QDebug>
#include <QPainter>
EQWidget::EQWidget(int count, AudioPlayer *player, SpectrumAnalyzer *analyzer,
                   QWidget *parent)
    : QWidget(parent), ui(new Ui::EQWidget) {
  ui->setupUi(this);
  this->player = player;
  this->barsCount = count;
  this->analyzer = analyzer;
}

EQWidget::~EQWidget() { delete ui; }
QSize EQWidget::minimumSizeHint() const { return QSize(100, 100); }

void EQWidget::updateEQ() {
  this->repaint();
  qDebug() << "updated";
}

QSize EQWidget::sizeHint() const { return QSize(200, 200); }

void EQWidget::paintEvent(QPaintEvent * /* event */) {

  QPainter painter(this);
  painter.setBrush(QBrush(Qt::blue));
  painter.setPen(QPen(Qt::white, 3));
  painter.setRenderHint(QPainter::Antialiasing, true);

  //  painter.setPen(palette().dark().color());
  //  painter.setBrush(Qt::NoBrush);
  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
