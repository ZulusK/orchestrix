#include "scorewindow.h"
#include "ui_scorewindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

ScoreWindow::ScoreWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreWindow)
{
    ui->setupUi(this);
    writeToFile();
    readFromJson();
    for (auto it = begin(players); it != end(players); it++) {
        Player *p = *it.base();
        qDebug() << p->get_name() << " | " << p->get_songName() << " | " << p->get_time();
    }
    drawTable(players);

    startWindow = new StartWindow();
    connect(startWindow, &StartWindow::scoreWindow, this, &ScoreWindow::show);
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}

void ScoreWindow::writeToFile(){
    for(int i = 0; i < 10; i++){
        Player *p = randomPlayer();
        players.push_back(p);
    }
    writeToJsonFile(players);
}

Player *ScoreWindow::randomPlayer(){
    Player *p = new Player();
    p->set_randomName();
    p->set_randomSongName();;
    p->set_randomTime();
    p->set_randomDifficulty();
    p->set_randomScore();
    return p;
}

void ScoreWindow::writeToJsonFile(vector<Player*> players){
    QJsonArray playerArray;
    for(auto player : players){
        QJsonObject playerObj;
        writeToJson(player, playerObj);
        playerArray.append(playerObj);
    }
    QJsonObject jPlayers;
    jPlayers["Players"] = playerArray;

    QJsonDocument saveDoc(jPlayers);
    QFile saveFile("Players.json");
    if ( !saveFile.open( QIODevice::WriteOnly ) )
    {
        qWarning( "Error: unable to open save file" );
        return;
    }
    saveFile.write( saveDoc.toJson() );
}

void ScoreWindow::writeToJson(Player *player, QJsonObject &json) {
    json["name"] = player->get_name();
    json["songName"] = player->get_songName();
    json["time"] = player->get_time();
    json["difficulty"] = player->get_difficulty();
    json["score"] = player->get_score();
}

void ScoreWindow::readFromJson()
{
    QString fileName = "Players.json";
    if (fileName.isEmpty()) {
        return;
    }

    load(fileName);
}

void ScoreWindow::load(const QString& fileName) {
    QFile loadFile(fileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject json = loadDoc.object();

    for (auto it = begin(players); it != end(players); it++) {
        Player *p = *it.base();
        p->parse(saveData);
    }
}

void ScoreWindow::drawTable(vector<Player*> players){
    int row = 0;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        for (auto it = begin(players); it != end(players); it++) {
            Player *p = *it.base();
                ui->tableWidget->setRowCount(row+1);
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(p->get_name()));
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(p->get_songName()));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(p->get_time())));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(p->get_difficulty())));
                ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(p->get_score())));
                row++;
        }
        ui->tableWidget->sortByColumn(4);
}

void ScoreWindow::on_backPushButton_clicked()
{
    for (Player *p : players) {
         delete p;
    }
    this->close();
    emit mainWindow();
}

void ScoreWindow::on_playPushButton_clicked()
{
    startWindow->show();
    this->close();
}
