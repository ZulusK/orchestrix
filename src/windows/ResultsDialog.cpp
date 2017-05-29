#include "ResultsDialog.h"
#include "ui_ResultsDialog.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>

#include "FileProcessing.h"

//
#include <QDebug>
#include <TableModel.h>
#include <User.h>

ResultsDialog::ResultsDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::ResultsDialog) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;
  //  User *u = new User("Lena", 23);
  //  User *u1 = new User("Danya", 89);
  //  User *u2 = new User("Vika", 44);
  //  User *u3 = new User("Alex", 5);
  //  User *u4 = new User("Anna", 78);
  //  User *u5 = new User("Sonya", 35);
  //  User *u6 = new User("Oleg", 38);
  //  User *u7 = new User("Kotik", 100);
  //  FileProcessing *f = new FileProcessing;
  drawTable("/Users/lena/projectX/res/results.json");
  //  f->users.push_back(u);
  //  f->users.push_back(u1);
  //  f->users.push_back(u2);
  //  f->users.push_back(u3);
  //  f->users.push_back(u4);
  //  f->users.push_back(u5);
  //  f->users.push_back(u6);
  //  f->users.push_back(u7);
  //  f->write("/Users/lena/projectX/res/results.json");
}

ResultsDialog::~ResultsDialog() { delete ui; }

void ResultsDialog::drawTable(const QString &filename) {
  FileProcessing *f = new FileProcessing;
  //  QString players = f->read(filename);
  f->load(filename);
  users = f->users;

  TableModel *model = new TableModel;
  QStandardItem *item;

  //Заголовки столбцов
  QStringList horizontalHeader;
  horizontalHeader.append("Name");
  horizontalHeader.append("Song");
  horizontalHeader.append("Score");
  horizontalHeader.append("Date");
  model->setHorizontalHeaderLabels(horizontalHeader);

  int row = 0;
  for (auto it = begin(users); it != end(users); it++) {
    User *u = *it.base();
    qDebug() << u->getName();
    qDebug() << "----------";
    qDebug() << u->getSoundName();
    qDebug() << "----------";
    qDebug() << u->getScore();
    qDebug() << "----------";
    qDebug() << u->getDate();
    qDebug() << "----------";

    item = new QStandardItem(u->getName());
    model->setItem(row, 0, item);

    item = new QStandardItem(u->getSoundName());
    model->setItem(row, 1, item);

    item = new QStandardItem(QString::number(u->getScore()));
    model->setItem(row, 2, item);

    item = new QStandardItem(u->getDate());
    model->setItem(row, 3, item);

    row++;
  }

  ui->tableView->setModel(model);

  ui->tableView->resizeColumnsToContents();
  ui->tableView->horizontalHeader()->setSectionResizeMode(3,
                                                          QHeaderView::Stretch);
}

// void ResultsDialog::load(const QString &jsonStr) {
//  qDebug() << jsonStr;
//  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonStr.toUtf8());
//  QJsonObject jsonObject = jsonDocument.object();
//  QJsonArray jsonArray = jsonObject["Users"].toArray();
//  // QJsonArray jsonArray = jsonDocument.array();
//  int cnt = jsonArray.size();
//  qDebug() << cnt;
//  for (int i = 0; i < cnt; i++) {
//    if (jsonArray[i].isObject()) {
//      QJsonObject jsonObject = jsonArray[i].toObject();
//      User *u = new User(jsonObject);
//      users.push_back(u);
//    }
//  }
//}
