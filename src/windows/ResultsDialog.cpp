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
  QPalette * palette = new QPalette();
  palette->setBrush(this->backgroundRole(), QBrush(QPixmap(":/res/fon.jpg")));
  this->setPalette(*palette);
}

ResultsDialog::~ResultsDialog() { delete ui; }

void ResultsDialog::drawTable(const QString &filename) {
  FileProcessing *f = new FileProcessing;
  QString players = f->read(filename);
  load(players);

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
  ui->tableView->setStyleSheet("QTableView::item {selection-color: black; "
                               "selection-background-color: rgba(0, 144, 255, "
                               "100);}");
}

void ResultsDialog::load(const QString &jsonStr) {
  qDebug() << jsonStr;
  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonStr.toUtf8());
  QJsonObject jsonObject = jsonDocument.object();
  QJsonArray jsonArray = jsonObject["Users"].toArray();
  // QJsonArray jsonArray = jsonDocument.array();
  int cnt = jsonArray.size();
  qDebug() << cnt;
  for (int i = 0; i < cnt; i++) {
    if (jsonArray[i].isObject()) {
      QJsonObject jsonObject = jsonArray[i].toObject();
      User *u = new User(jsonObject);
      users.push_back(u);
    }
  }
}
