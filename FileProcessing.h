#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <QString>
#include <User.h>
#include <vector>

class FileProcessing {
public:
  FileProcessing();
~FileProcessing();
  QString read(const QString &filename);
  void write(const QString &filename);
  void load(const QString &filename);
  std::vector<User *> *getUsers() const;

private:
  std::vector<User *>  *users;
};

#endif // FILEPROCESSING_H
