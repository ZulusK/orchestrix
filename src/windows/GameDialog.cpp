#include "GameDialog.h"
#include "ui_GameDialog.h"

GameDialog::GameDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialog) {
  ui->setupUi(this);
  this->environment = game;
}

GameDialog::~GameDialog() { delete ui; }
