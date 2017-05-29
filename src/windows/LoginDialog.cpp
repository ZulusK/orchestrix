#include "LoginDialog.h"
#include "ui_LoginDialog.h"

//
#include <QDebug>

LoginDialog::LoginDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
  this->environment = game;
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::on_pushButton_2_clicked() {
  qDebug() << "1----";
  if (environment->getUser() != NULL) {
    environment->removeUser();
  }
  environment->addUser(new User(ui->nameEdit->text()));
  this->reject();
}

void LoginDialog::on_pushButton_clicked() {
  qDebug() << "1+++++";
  if (environment->getUser() != NULL) {
    environment->removeUser();
  }
  environment->addUser(new User("Vasya"));
  this->accept();
}

void LoginDialog::on_spinBox_valueChanged(int arg1) {
  ui->horizontalSlider->setValue(arg1);
}

void LoginDialog::on_horizontalSlider_valueChanged(int value) {
  ui->spinBox->setValue(value);
}
