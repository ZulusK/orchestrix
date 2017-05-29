#include "FileProcessing.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTextStream>

bool compare(User *a, User *b) { return a->getScore() > b->getScore(); }

FileProcessing::FileProcessing() { this->users = new std::vector<User *>; }

QString FileProcessing::read(const QString &filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    qDebug() << "Can't find file" + filename;
    return "";
  }
  QTextStream in(&file);
  QString text;
  text = in.readAll();
  file.close();
  return text;
}

void FileProcessing::write(const QString &filename) {
  std::sort(users->begin(), users->end(), compare);
  QJsonArray *usersArray = new QJsonArray();
  for (auto it = users->begin(); it != users->end(); it++) {
    auto u = *it;
    QJsonObject userObj = u->toJSON();
    usersArray->append(userObj);
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
  delete usersArray;
}

FileProcessing::~FileProcessing() {
  for (auto u : *users) {
    delete u;
  }
  users->clear();
  delete users;
}

bool contains(std::vector<User *> *users, User *u) {
  for (auto it = users->begin(); it != users->end(); it++) {
    if ((*it)->equals(u)) {
      delete u;
      return true;
    }
  }
  return false;
}

void FileProcessing::load(const QString &filename) {
  QString jsonStr = read(filename);
  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonStr.toUtf8());
  QJsonObject jsonObject = jsonDocument.object();
  QJsonArray jsonArray = jsonObject["Users"].toArray();
  int cnt = jsonArray.size();
  for (int i = 0; i < cnt; i++) {
    if (jsonArray[i].isObject()) {
      QJsonObject jsonObject = jsonArray[i].toObject();
      User *u = new User(jsonObject);
      if (!contains(users, u)) {
        users->push_back(u);
      }
    }
  }
}

std::vector<User *> *FileProcessing::getUsers() const { return users; }
