#ifndef USER_H
#define USER_H
#include <QJsonObject>
#include <QString>

class User {
private:
  QString name;
  QString soundName;
  long long score;
  QString date;

public:
  User(QString name);
  User(const QString &jsonStr,int a);
  const QString &getName();
  const QString &getSoundName();
  long getScore();
  const QString &getDate();
  void addToScore(int val);
  ~User();
  QJsonObject *toJSON();
  QString toString();

  void setScore(long long value);
  void setSoundName(const QString &value);
};

#endif // USER_H
