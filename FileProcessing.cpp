#include "FileProcessing.h"

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
