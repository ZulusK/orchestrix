#include "GameDialog.h"
#include "ui_GameDialog.h"

GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);
}

GameDialog::~GameDialog()
{
    delete ui;
}
