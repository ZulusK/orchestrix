#include "Indicator.h"
#include <QStyle>
#include <chrono>
#include <iostream>
using namespace std;
long inline currentTime() {
  auto now = std::chrono::system_clock::now();
  auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
  auto value = now_ms.time_since_epoch();
  long duration = value.count();
  return duration;
}

Indicator::Indicator(int id, const QString &style, QPushButton *button,
                     GameDialog *parent) {
  this->id = id;
  this->button = button;
  this->parent = parent;
  this->createdTime = -1;
  this->timePeriod = -1;
  this->buttonStyle = style;
  this->button->hide();
  update();
}

QString getColor(float progress) {
  if (progress > 1) {
    progress = 1;
  }
  int r = RED_START + (RED_END - RED_START) * progress;
  int g = GREEN_START + (GREEN_END - GREEN_START) * progress;
  int b = BLUE_START + (BLUE_END - BLUE_START) * progress;

  int a = 255 * progress;
  QString s = "rgba(" + QString::number(r) + "," + QString::number(g) + "," +
              QString::number(b) + "," + QString::number(a) + ")";
  cout << s.toStdString() << endl;
  return s;
}

QString getRadius(float progress) {
  if (progress > 1) {
    progress = 1;
  }
  return "border-radius: " + QString::number(5+45 * progress) + "%";
}

void Indicator::update() {
  if (timePeriod >= 0) {
    float progress = (currentTime() - createdTime) / (float)timePeriod;
    button->show();
    button->setStyleSheet(buttonStyle + getColor(progress) + ";\n" +
                          getRadius(progress) + ";\n");
    if (progress > 1) {
      parent->indicatorEnd(this);
      return;
    }
    cout << id << " : " << progress << endl;
    QString style;

  } else {
    button->setStyleSheet(buttonStyle + getColor(0) + ";\n" + getRadius(0) +
                          ";\n");
    button->hide();
  }
}

Indicator::~Indicator() {
  this->timePeriod = -1;
  update();
}

int Indicator::getId() const { return id; }

void Indicator::setId(int value) { id = value; }

QPushButton *Indicator::getButton() const { return button; }

void Indicator::setButton(QPushButton *value) { button = value; }

void Indicator::setPeriod(long value) {
  timePeriod = value;
  this->createdTime = currentTime();
}
