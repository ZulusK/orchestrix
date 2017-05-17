#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <AudioData.h>
#include <AudioPlayer.h>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <Spectrum.h>
#include <SpectrumAnalyzer.h>

namespace Ui {
class EQWidget;
}

class EQWidget : public QWidget {
  Q_OBJECT

public:
  explicit EQWidget(int count, AudioPlayer *player, SpectrumAnalyzer *analyzer,
                    QWidget *parent = 0);
  ~EQWidget();
  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;
  void updateEQ();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  Ui::EQWidget *ui;
  QPixmap backgoundImage;
  AudioPlayer *player;
  SpectrumAnalyzer *analyzer;
  int barsCount;
};

#endif // EQWIDGET_H
