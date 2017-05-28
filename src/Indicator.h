#ifndef INDICATOR_H
#define INDICATOR_H
#include <GameDialog.h>
#include <QPushButton>

enum {
  RED_START = 241,
  RED_END = 255,
  GREEN_START = 61,
  GREEN_END = 0,
  BLUE_START = 0,
  BLUE_END = 0
};
class GameDialog;

class Indicator {

public:
  Indicator(int id, const QString &style, QPushButton *button,
            GameDialog *parent);
  ~Indicator();
  void clear();

  void setPeriod(long value);

  QPushButton *getButton() const;
  void setButton(QPushButton *value);
  bool isBusy();
  int getId() const;
  void setId(int value);

private:
  void end();
  void start();
  void buttonSetColor(double val);

public slots:
  void update();

private:
  long createdTime;
  long timePeriod;
  GameDialog *parent;
  int id;
  QPushButton *button;
  QString buttonStyle;
};

#endif // INDICATOR_H
