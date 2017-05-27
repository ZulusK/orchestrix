#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <QString>
#include <vector>

class QJsonObject;

using namespace std;

class Player
{
    QString  _name;
    QString  _songName;
    double _time;
    int _difficulty;
    int _score;

public:
    Player(const QString & name, const QString &songName, double time, int difficulty, int score);

    Player();
    ~Player();

    void set_name(QString name);
    void set_songName(QString songName);
    void set_time(double time);
    void set_difficulty(int difficulty);
    void set_score(int score);

    QString get_name();
    QString get_songName();
    double get_time();
    int get_difficulty();
    int get_score();

    void set_randomName();
    void set_randomSongName();
    void set_randomTime();
    void set_randomDifficulty();
    void set_randomScore();

    QString get_name(const QJsonObject &jsonObject);
    QString get_songName(const QJsonObject &jsonObject);
    double get_time(const QJsonObject &jsonObject);
    int get_difficulty(const QJsonObject &jsonObject);
    int get_score(const QJsonObject &jsonObject);
    Player *parse(const QString &jsonStr);


};
#endif // PLAYER_H
