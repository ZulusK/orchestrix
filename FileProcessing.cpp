#include "FileProcessing.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

FileProcessing::FileProcessing()
{

}

QString FileProcessing::read(const QString &filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
        return "";

    QTextStream in(&file);
    QString text;
    text = in.readAll();
    return text;
}

void FileProcessing::write(const QString &filename){
//    QJsonArray usersArray;
//        for(auto u : users){
//            QJsonObject *userObj = u->toJSON();
//            usersArray.append(userObj);
//        }
//        QJsonObject jUsers;
//        jUsers["Users"] = usersArray;

//        QJsonDocument saveDoc(jUsers);
//        QFile saveFile(filename);
//        if ( !saveFile.open( QIODevice::WriteOnly ) )
//        {
//            qWarning( "Error: unable to open save file" );
//            return;
//        }
//        saveFile.write( saveDoc.toJson() );
}
