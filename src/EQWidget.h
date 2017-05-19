#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <AudioData.h>
#include <AudioPlayer.h>
#include <QBrush>
#include <QColor>
#include <QMap>
#include <QPen>
#include <QPixmap>
#include <QPointF>
#include <QRectF>
#include <QTimer>
#include <QWidget>
#include <Spectrum.h>
#include <SpectrumAnalyzer.h>

#define SPACE_BORDER 0.01

typedef enum { RECT = 0x1, LINE, AREA } EQShape;

namespace Ui {
class EQWidget;
}
/**
 * @brief The EQWidget class defines new EQ widget
 */
class EQWidget : public QWidget {
  Q_OBJECT

  Ui::EQWidget *ui;
  AudioPlayer *player;
  SpectrumAnalyzer *analyzer;
  QTimer *timer;
  QPointF **bars;

  int barsCount;
  long sleepTime;
  unsigned long lastUpdateTime;
  unsigned long spectrumPos;
  bool isPaused;
  int lineWidth;
  EQShape barType;
  QPen pen;
  QBrush brush;
  bool antialiased;

public slots:
  void setShape(EQShape shape);
  void setPen(const QPen &pen);
  void setBrush(const QBrush &brush);
  void setAntialiased(bool antialiased);

public:
  /**
   * @brief EQWidget constructor
   * @param player sound player to sync
   * @param analyzer spectrum sound analyzer
   * @param parent widget parent of EQ
   */
  explicit EQWidget(AudioPlayer *player, SpectrumAnalyzer *analyzer,
                    QWidget *parent = 0);
  /**
   * @brief ~EQWidget destructor
   */
  ~EQWidget();

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
   * @brief updateEQ update EQ immediately
   */
  void updateEQ();
  /**
   * @brief setEQShape set current EQ bar's type
   * @param newType new type of bars (LINE or RECT)
   */
  void setEQShape(EQShape newType);
  /**
   * @brief pause pause updating EQ
   */
  void pause();
  /**
   * @brief start continue updating EQ
   */
  void start();
  /**
   * @brief getState check, is EQ was paused
   * @return true, if EQ is paused, else - false
   */
  bool getState();
  /**
   * @brief getSpectrumPos get current spectrum position
   * @return current spectrum position
   */
  unsigned long getSpectrumPos();
  /**
   * @brief getEQShape get current EQ's bars shape type
   * @return current EQ's bars shape type
   */
  EQShape getEQShape();

protected:
  void paintEvent(QPaintEvent *event) override;
private slots:
  void updateBars();

private:
  void updateSpectrumPos();
  void timerLoopInit();
  void drawRectBars(QPainter &painter);
  void drawLineBars(QPainter &painter);
  void drawAreaBars(QPainter &painter);
};

#endif // EQWIDGET_H
