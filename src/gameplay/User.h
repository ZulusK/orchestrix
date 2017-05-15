#ifndef USER_H
#define USER_H
#include <QString>

enum { EASY = 0xFEA, MEDIUM, HARD };
class User {
  QString name;
  int difficult;

public:
  User(const QString &name, int difficult);
  void setDifficult(int difficult);
};

#endif // USER_H
