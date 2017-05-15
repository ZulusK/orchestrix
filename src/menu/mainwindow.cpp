#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startWindow = new StartWindow();
    connect(startWindow, &StartWindow::mainWindow, this, &MainWindow::show);

    scoreWindow = new ScoreWindow();
    connect(scoreWindow, &ScoreWindow::mainWindow, this, &MainWindow::show);

    helpWindow = new HelpWindow();
    connect(helpWindow, &HelpWindow::mainWindow, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setScorePushButton_clicked()
{
    scoreWindow->show();
    this->close();
}




void MainWindow::on_startPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "Images (*.png *.xpm *.jpg);;All files (*.*)");

    startWindow->show();
    this->close();
}

void MainWindow::on_helpPushButton_clicked()
{
    helpWindow->show();
    this->close();
}

void MainWindow::on_exitPushButton_clicked()
{
     close();
}

void MainWindow::on_signUpPushButton_clicked()
{

}

void MainWindow::on_logInPushButton_clicked()
{

}

