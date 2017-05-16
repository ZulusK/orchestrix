#include "player.h"
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <vector>
#include <QFile>


Player::Player(const QString  & name, const QString  &songName, double time, int difficulty, int score){

    this->_name = name;
    this->_songName = songName;
    this->_time = time;
    this->_difficulty = difficulty;
    this->_score = score;
}

Player::Player()
{
    this->_name = "";
    this->_songName = "";
    this->_time = 0.0;
    this->_difficulty = 0;
    this->_score = 0;
}

Player::~Player()
{
    cout << "Player is destoyed!" << endl;
}

void Player::set_name(QString name){this->_name = name;}
void Player::set_songName(QString songName){this->_songName = songName;}
void Player::set_time(double time){this->_time = time;}
void Player::set_difficulty(int difficulty){this->_difficulty = difficulty;}
void Player::set_score(int score){this->_score = score;}

QString Player::get_name(){return this->_name;}
QString Player::get_songName(){return this->_songName;}
double Player::get_time(){return this->_time;}
int Player::get_difficulty(){return this->_difficulty;}
int Player::get_score(){return this->_score;}

void Player::set_randomName()
{
    QString name[] = {"Jacob","Emily","Michael","Emma","Joshua","Madison","Matthew","Olivia","Ethan","Hannah","Andrew","Abigail",
                      "Daniel","Isabella","William","Ashley","Joseph","Samantha","Christopher","Elizabeth","Anthony","Alexis",
                      "Ryan","Sarah","Nicholas","Grace","David","Alyssa","Alexander","Sophia"};
    int cnt = sizeof(name)/sizeof(name[0]);
    QString randomName = name[qrand() % cnt];
    this->_name = randomName;
}
void Player::set_randomSongName()
{
    QString songName[] = {"Adrian","Benson","Bradley","Crystal","Edwards","Brown","Joy","Johnson","Dee","Tucker","West","Haley",
                      "Johnson","Love","Simon","Eden","Foster","Gibson","Franklin","Elizabeth","Peters","Kimberly",
                      "King","Miller","Toni","Robin","Lynn","Florence","Kotik","Carr"};
    int cnt = sizeof(songName)/sizeof(songName[0]);
    QString randomSongName = songName[qrand() % cnt];
    this->_songName = randomSongName;
}
void Player::set_randomTime()
{
    this->_time = qrand() % 10;
}
void Player::set_randomDifficulty(){
    this->_difficulty = qrand() % 11;
}
void Player::set_randomScore(){
    this->_score = qrand() % 10000;
}



QString Player::get_name(const QJsonObject &jsonObject){
    return jsonObject[QString::fromStdString("name")].toString();
}

QString Player::get_songName(const QJsonObject &jsonObject){
    return jsonObject[QString::fromStdString("songName")].toString();
}

double Player::get_time(const QJsonObject &jsonObject){
    return jsonObject[QString::fromStdString("time")].toDouble();
}

int Player::get_difficulty(const QJsonObject &jsonObject){
    return jsonObject[QString::fromStdString("difficulty")].toInt();
}

int Player::get_score(const QJsonObject &jsonObject){
    return jsonObject[QString::fromStdString("score")].toInt();
}

Player *Player::parse(const QString &jsonStr){
    Player *newPlayer = new Player;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonStr.toUtf8());
    if(jsonDocument.isObject()){
        QJsonObject jsonObject = jsonDocument.object();
        newPlayer->_name = get_name(jsonObject);
        newPlayer->_songName = get_songName(jsonObject);
        newPlayer->_time = get_time(jsonObject);
        newPlayer->_difficulty = get_difficulty(jsonObject);
        newPlayer->_score = get_score(jsonObject);
    }
    return newPlayer;
}


