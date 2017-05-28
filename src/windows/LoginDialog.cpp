#include "LoginDialog.h"
#include "ui_LoginDialog.h"

LoginDialog::LoginDialog(Game * game,QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
  this->environment=game;
  QPalette * palette = new QPalette();
  palette->setBrush(this->backgroundRole(), QBrush(QPixmap(":/res/fon2.jpg")));
  this->setPalette(*palette);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::on_pushButton_2_clicked() { this->reject(); }

void LoginDialog::on_pushButton_clicked() { this->accept(); }

void LoginDialog::on_spinBox_valueChanged(int arg1) {
  //ui->horizontalSlider->setValue(arg1);
}

void LoginDialog::on_horizontalSlider_valueChanged(int value)
{
   // ui->spinBox->setValue(value);
}
