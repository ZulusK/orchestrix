#include "GameDialog.h"
#include "ui_GameDialog.h"
#include <QTimer>
GameDialog::GameDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;

  this->eqwidget = new EQWidget(40, NULL, NULL, this);
  ui->centralGrid->addWidget(eqwidget, 1, 0, 1, 2);
  QTimer *timer = new QTimer(this);
//  updateEq
}

GameDialog::~GameDialog() { delete ui; }

void GameDialog::updateEQ() {
  eqwidget->updateEQ();
}
