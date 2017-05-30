#include "HelpDialog.h"
#include "ui_HelpDialog.h"
#include "QFile"
#include <QByteArray>


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

    QFont serifFont("URW Bookman L", 25, QFont::Normal);
    ui->textEdit->setFont(serifFont);

    QFile file(":/res/help.txt");
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    data = file.readAll();

    ui->textEdit->setText(QString::fromStdString(data.toStdString()));
    ui->textEdit->setReadOnly(true);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
