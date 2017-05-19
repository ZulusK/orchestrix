#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <AudioData.h>
#include <AudioPlayer.h>
#include <QBrush>
#include <QLineF>
#include <QMap>
#include <QPair>
#include <QParallelAnimationGroup>
#include <QPen>
#include <QPixmap>
#include <QPointF>
#include <QPropertyAnimation>
#include <QRectF>
#include <QTimer>
#include <QWidget>
#include <Spectrum.h>
#include <SpectrumAnalyzer.h>
#define SPACE_BORDER 40
namespace Ui {
class EQWidget;
}

class EQWidget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(QLineF barHeight WRITE setBar NOTIFY changeEvent)

public:
  explicit EQWidget(AudioPlayer *player, SpectrumAnalyzer *analyzer,
                    QWidget *parent = 0);
  ~EQWidget();
  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;
  void updateEQ();
  void setBar(QLineF &bar);

protected:
  void paintEvent(QPaintEvent *event) override;
private slots:
  void updateBars();
signals:
  void eqChanged();

private:
  QPropertyAnimation **createAnimators(int count);
  QPropertyAnimation **animators;
  void updateSpectrumPos();
  Ui::EQWidget *ui;
  AudioPlayer *player;
  SpectrumAnalyzer *analyzer;
  unsigned long spectrumPos;
  QTimer *updateTimer;
  QMap<int, QPointF> barsMap;
  QParallelAnimationGroup groupAnimation;
  int barsCount;
  double sleepTime;
  double lastUpdate;
};

#endif // EQWIDGET_H
