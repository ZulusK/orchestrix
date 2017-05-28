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
    QPalette * palette = new QPalette();
    palette->setBrush(this->backgroundRole(), QBrush(QPixmap(":/res/fon.jpg")));
    this->setPalette(*palette);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
