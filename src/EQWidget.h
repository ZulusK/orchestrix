#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <AudioData.h>
#include <AudioPlayer.h>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
#include <Spectrum.h>
#include <SpectrumAnalyzer.h>

#define SPACE_BORDER 10
namespace Ui {
class EQWidget;
}

class EQWidget : public QWidget {
  Q_OBJECT

public:
  explicit EQWidget(AudioPlayer *player, SpectrumAnalyzer *analyzer,
                    QWidget *parent = 0);
  ~EQWidget();
  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;
  void updateEQ();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void updateSpectrumPos();
  Ui::EQWidget *ui;
  QPixmap backgoundImage;
  AudioPlayer *player;
  SpectrumAnalyzer *analyzer;
  int barsCount;
  unsigned long spectrumPos;

};

#endif // EQWIDGET_H
