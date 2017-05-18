#ifndef USER_H
#define USER_H
#include <QJsonObject>
#include <QString>

class User {
private:
  QString name;
  QString soundName;
  long long score;

public:
  User(QString name);
  const QString &getName();
  const QString &getSoundName();
  void addToScore(int val);
  ~User();
  QJsonObject *toJSON();
  QString toString();
};

#endif // USER_H
