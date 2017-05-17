#include "ResultsDialog.h"
#include "ui_ResultsDialog.h"

ResultsDialog::ResultsDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::ResultsDialog) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window);
  this->showFullScreen();
  this->environment = game;
}

ResultsDialog::~ResultsDialog() { delete ui; }
