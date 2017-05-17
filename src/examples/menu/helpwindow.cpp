#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
}

HelpWindow::~HelpWindow()
{
    delete ui;
}

void HelpWindow::on_backPushButton_clicked()
{
    this->close();
    emit mainWindow();
}
