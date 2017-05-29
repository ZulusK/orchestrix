#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QDebug>

LoginDialog::LoginDialog(Game *game, QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
  this->environment = game;
  QPalette *palette = new QPalette();
  palette->setBrush(this->backgroundRole(), QBrush(QPixmap(":/res/fon2.jpg")));
  this->setPalette(*palette);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::reject() {
    if(environment->getUser()==NULL){
         environment->addUser(new User("Vasya"));
    }
    QDialog::reject();
}


void LoginDialog::accept() {
  if (environment->getUser() != NULL) {
    environment->removeUser();
  }
  if(ui->nameEdit->text().length()==0){
      environment->addUser(new User("Vasya"));
  }else{
      environment->addUser(new User(ui->nameEdit->text()));
  }
  QDialog::accept();
}
