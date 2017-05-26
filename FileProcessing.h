#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <QString>
#include <vector>
#include <User.h>

class FileProcessing
{
public:
    FileProcessing();

    QString read(const QString &filename);
    void write(const QString &filename);

    std::vector<User*> users;
};

#endif // FILEPROCESSING_H
