#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <equalizer.h>
#include <QtGui>
#include <QtCore>

#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <lineconnector.h>
#include <random>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


////////////Generating random double array for testing(simulation of fft data) 1..20 range/////////////
    qsrand(QTime::currentTime().msec());
    int numOfPoints = 20;
    double fMin = 0;
    double fMax = 20;
    double randomTestArray[numOfPoints];
    srand(time(NULL));

    for(int i = 0 ; i < numOfPoints ; i++)
    {
        randomTestArray[i] = fMin + (double)rand() * (fMax - fMin) / RAND_MAX;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////



    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setStyleSheet("background:transparent");
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);


    for(int i = 0 ; i < numOfPoints; i++)
    {
       Equalizer * eq = new Equalizer(i , randomTestArray[i] , i);
       eq->setFlag(QGraphicsItem::ItemIsMovable);
       scene->addItem(eq);
    }


    for(int i = 0; i < numOfPoints; i = i + 2)
    {
        LineConnector * lc = new LineConnector(i , randomTestArray[i] , randomTestArray[i+1]);
        scene->addItem(lc);
    }


    QTimer * timer = new QTimer(this);
    connect(timer , SIGNAL(timeout()), scene , SLOT(advance()));
    timer->start(5);


}

MainWindow::~MainWindow()
{
    delete ui;
}
