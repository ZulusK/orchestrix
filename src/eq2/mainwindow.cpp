#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <../EqOrch/equalizer.h>
#include <QGraphicsScene>
#include <QThread>
#include <QTime>
#include <QDebug>
#include <QThread>
#include <thread>
#include <mutex>
#include <QTimer>
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


            int numberOfBars = 24;
            int numberOfChunks = 100;



            int numbOfRepaints = 50;
            int startArray[24];
            for(int i = 0 ; i < 24 ; i++)
            {
                startArray[i] = -1;
            }

            int numOfPoints = 20;


            Equalizer * eq = new Equalizer();
            ui->verticalLayout->addWidget(eq);

            double randomTestArray[numOfPoints];
            double fMin = 0;
            double fMax = 20;
            srand(time(NULL));

            for(int p = 0 ; p < 100 ; p++)
            {

                for(int i = 0 ; i < numOfPoints ; i++)
                {
                    randomTestArray[i] = fMin + (double)rand() * (fMax - fMin) / RAND_MAX;
                }
                QCoreApplication::processEvents(QEventLoop::AllEvents);
                eq->setChunk(&randomTestArray[0] , &startArray[0]);
            }


}

MainWindow::~MainWindow()
{
    delete ui;
}

