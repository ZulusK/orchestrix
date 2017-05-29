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
  // copy ref
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;

  // customize
  QPalette *palette = new QPalette();
  palette->setBrush(this->backgroundRole(), QBrush(QPixmap(":/res/fon.jpg")));
  this->setPalette(*palette);

  // add users to table
  drawTable();
}

ResultsDialog::~ResultsDialog() { delete ui; }

void ResultsDialog::drawTable() {
  environment->updateStorage();
  auto users = environment->getStorage()->getUsers();
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
  for (auto it = users->begin(); it != users->end(); it++) {
    User *u = *it.base();

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
