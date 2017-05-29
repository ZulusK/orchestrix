#include "FileProcessing.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTextStream>

bool compare(User *a, User *b) { return a->getScore() > b->getScore(); }

FileProcessing::FileProcessing() {}

QString FileProcessing::read(const QString &filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QFile::Text))
    return "";

  QTextStream in(&file);
  QString text;
  text = in.readAll();
  return text;
}

void FileProcessing::write(const QString &filename) {
  std::sort(users.begin(), users.end(), compare);
  QJsonArray *usersArray = new QJsonArray();
  for (auto u : users) {
    QJsonObject *userObj = u->toJSON();
    usersArray->append(*userObj);
  }
  QJsonObject jUsers;
  jUsers["Users"] = *usersArray;

  QJsonDocument saveDoc(jUsers);
  QFile saveFile(filename);
  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Error: unable to open save file");
    return;
  }
  saveFile.write(saveDoc.toJson());
}

void FileProcessing::load(const QString &filename) {
  QString jsonStr = read(filename);
  qDebug() << jsonStr;
  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonStr.toUtf8());
  QJsonObject jsonObject = jsonDocument.object();
  QJsonArray jsonArray = jsonObject["Users"].toArray();
  // QJsonArray jsonArray = jsonDocument.array();
  int cnt = jsonArray.size();
  qDebug() << cnt;
  for (int i = 0; i < cnt; i++) {
    if (jsonArray[i].isObject()) {
      QJsonObject jsonObject = jsonArray[i].toObject();
      User *u = new User(jsonObject);
      users.push_back(u);
    }
  }
}
