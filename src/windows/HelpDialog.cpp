#include "HelpDialog.h"
#include "ui_HelpDialog.h"

HelpDialog::HelpDialog(Game * game,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->showFullScreen();
    this->environment=game;
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
