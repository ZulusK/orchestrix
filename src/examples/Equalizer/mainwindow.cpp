#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>
#include <QThread>
#include <QTime>
#include <QDebug>
#include <QThread>
#include <QSignalTransition>
#include <QTimer>
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // Initializing array that would contain y coordinates of previous state
    for(int i = 0 ; i < 24 ; i++)
    {
        startArray[i] = -1;
    }


    // Creating timer that would play the role of a loop
    eq = new Equalizer();
    ui->verticalLayout->addWidget(eq); // Adding widget to vertical layout that should be created by the client

    QTimer * timer = new QTimer(this);
    int timerDuration = 2000;  // !!!!!! Play around with this value to adjust to data + (animationDuration value in equalizer.cpp)
    connect(timer , SIGNAL(timeout()) , this ,SLOT(iterate()));
    timer->start(timerDuration);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Slot that is invoked by Timer
void MainWindow::iterate()
{

    int numOfBars = 20; // Number of circles(lines)

    // Generating random double array that would simulate fft data
    double randomTestArray[numOfBars];
    double fMin = 0;
    double fMax = 20;
    srand(time(NULL));

    for(int i = 0 ; i < numOfBars ; i++)
    {
        randomTestArray[i] = fMin + (double)rand() * (fMax - fMin) / RAND_MAX;
    }

    QCoreApplication::processEvents();
    eq->setChunk(&randomTestArray[0] , &startArray[0]);  // Invoking method that sets up QAnimationProperty animation

}

