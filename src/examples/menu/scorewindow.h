#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include <QWidget>
#include <QStandardItem>
#include "player.h"
#include <vector>
#include <QJsonObject>
#include "startwindow.h"


namespace Ui {
class ScoreWindow;
}

class ScoreWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreWindow(QWidget *parent = 0);
    ~ScoreWindow();

signals:
    void mainWindow();

private slots:
    void on_backPushButton_clicked();

    void on_playPushButton_clicked();

private:
    Ui::ScoreWindow *ui;

    vector<Player*> players;

    void writeToFile();
    void writeToJsonFile(vector<Player*> players);
    void writeToJson(Player *player, QJsonObject &json);

    void readFromJson();
    void load(const QString& fileName);
    void drawTable(vector<Player*> players);

    Player *randomPlayer();
    StartWindow *startWindow;
};

#endif // SCOREWINDOW_H
