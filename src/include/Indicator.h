#ifndef INDICATOR_H
#define INDICATOR_H
#include <GameDialog.h>
#include <QPushButton>
#include <Controller.h>
//start rgb(0, 126, 255);
//end rgb(0, 255, 20)
enum {
  RED_START = 0,
  RED_END = 0,
  GREEN_START = 126,
  GREEN_END = 255,
  BLUE_START = 255,
  BLUE_END = 20
};
class GameDialog;

class Indicator {

public:
  Indicator(int id, const QString &style, QPushButton *button,Controller * controller,
            GameDialog *parent);
  ~Indicator();
  void clear();

  void setPeriod(long value);

  QPushButton *getButton() const;
  void setButton(QPushButton *value);
  bool isBusy();
  int getId() const;
  void setId(int value);

  unsigned long getCurPos() const;
  void setCurPos(unsigned long value);

  long getTimePeriod() const;

private:
  void end();
  void start();
  void buttonSetColor(double val);

public slots:
  bool update();

private:
  unsigned long curPos;
  long createdTime;
  long timePeriod;
  GameDialog *parent;
  int id;
  QPushButton *button;
  QString buttonStyle;
  Controller * controller;
};

#endif // INDICATOR_H
