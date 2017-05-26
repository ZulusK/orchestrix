#include "ResultsDialog.h"
#include "ui_ResultsDialog.h"

#include "FileProcessing.h"

ResultsDialog::ResultsDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::ResultsDialog) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;
  //drawTable(const String &filename);
}

ResultsDialog::~ResultsDialog() { delete ui; }

void ResultsDialog::drawTable(const QString &filename){
    FileProcessing f;
    QString players = f.read(filename);
    load(players);
    int row = 0;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        for (auto it = begin(users); it != end(users); it++) {
            User *u = *it.base();
                ui->tableWidget->setRowCount(row+1);
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(u->getName()));
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(u->getSoundName()));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(u->getScore())));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(u->getDate()));
                row++;
        }
        ui->tableWidget->sortByColumn(2);
}

void ResultsDialog::load(const QString &jsonStr){
    for (int i = 0; i < 10;i++) {
         User *u = new User(jsonStr, 1);
         users.push_back(u);
       }
}
