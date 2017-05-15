#include "User.h"

User::User(const QString &name, int difficult) {
  this->name = name;
  setDifficult(difficult);
}

void User::setDifficult(int difficult) {
  if (difficult == EASY || difficult == MEDIUM || difficult == HARD) {
    this->difficult = difficult;
  } else {
    difficult = MEDIUM;
  }
}
