#include "MenuDialog.h"
#include "ui_MenuDialog.h"

MenuDialog::MenuDialog(Game *env, fQWidget *parent)
    : QDialog(parent), ui(new Ui::MenuDialog) {
  this->environment = env;
  ui->setupUi(this);
}

MenuDialog::~MenuDialog() { delete ui; }
