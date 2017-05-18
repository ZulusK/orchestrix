#include "User.h"
#include <QDateTime>
#include <QJsonDocument>

User::User(QString name) {
  this->name = name;
  this->soundName = "Not selected";
  this->score = 0;
}

const QString &User::getName() { return this->name; }

const QString &User::getSoundName() { return this->soundName; }

void User::addToScore(int val) { this->score += val; }

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
