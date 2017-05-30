#ifndef SOUNDHISTOGRAMM_H
#define SOUNDHISTOGRAMM_H

#include <AudioData.h>
#include <AudioPlayer.h>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
namespace Ui {
class SoundHistogramm;
}

class SoundHistogramm : public QWidget {
  Q_OBJECT

public:
  explicit SoundHistogramm(const QPen &pen, AudioPlayer *player,
                           AudioData *sound, QWidget *parent = 0);
  ~SoundHistogramm();
  /**
   * @brief minimumSizeHint get EQ minimum size
   * @return EQ minimum size
   */
  QSize minimumSizeHint() const override;
  /**
   * @brief sizeHint get EQ's current size
   * @return EQ's current size
   */
  QSize sizeHint() const override;
  /**
   * @brief start start executing histogramm updating
   */
  void start();
public slots:
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setAntialiased(bool antialiased);
  void updateHistogramm();

private:
  QPixmap *createImage();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  Ui::SoundHistogramm *ui;
  AudioPlayer *player;
  AudioData *sound;
  QPixmap *image;
  QTimer *timer;
  bool antialiased;
  long remainingTime;
  QPen pen;
  QBrush brush;
};

#endif // SOUNDHISTOGRAMM_H
