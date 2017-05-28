#include "User.h"
#include <QDateTime>
#include <QJsonDocument>

void User::setScore(long long value) {
  mut.lock();
  score = value;
  mut.unlock();
}

void User::setSoundName(const QString &value) { soundName = value; }

User::User(QString name) {
  this->name = name;
  this->soundName = "Not selected";
  this->score = 0;
}
//
User::User(QString name, int score) {
  this->name = name;
  this->soundName = "Not selected";
  this->score = score;
}

User::User(const QJsonObject &jsonObject) {
  this->name = jsonObject[QString::fromStdString("name")].toString();
  this->soundName = jsonObject[QString::fromStdString("sound")].toString();
  this->score = jsonObject[QString::fromStdString("score")].toInt();
  this->date = jsonObject[QString::fromStdString("date")].toString();
}

const QString &User::getName() { return this->name; }

const QString &User::getSoundName() { return this->soundName; }

long User::getScore() { return this->score; }

const QString &User::getDate() { return this->date; }

void User::addToScore(int val) {
  mut.lock();
  this->score += val;
  mut.unlock();
}

User::~User() {}

QJsonObject *User::toJSON() {
  QJsonObject *jobj = new QJsonObject();
  (*jobj)[QString("name")] = this->name;
  (*jobj)[QString("sound")] = this->soundName;
  (*jobj)[QString("date")] = QDateTime::currentDateTime().toString();
  (*jobj)[QString("score")] = this->score;
  return jobj;
}

QString User::toString() {
  auto jobj = toJSON();
  QJsonDocument doc(*jobj);
  QString jstr(doc.toJson(QJsonDocument::Compact));
  delete jobj;
  return jstr;
}
