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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


            int numbOfRepaints = 50;
            int * startYArr = NULL;
            int numOfPoints = 20;



            double randomTestArray[numOfPoints];
            double fMin = 0;
            double fMax = 20;

            for(int p = 0 ; p < numbOfRepaints ; p++)
            {
                srand(time(NULL));
                for(int i = 0 ; i < numOfPoints ; i++)
                {
                    randomTestArray[i] = fMin + (double)rand() * (fMax - fMin) / RAND_MAX;
                }

                Equalizer * eq = new Equalizer();
                ui->verticalLayout->addWidget(eq);
                startYArr = eq->setChunk(&randomTestArray[0] , startYArr);
                delete ui->verticalLayout->takeAt(0);
            }


}

MainWindow::~MainWindow()
{
    delete ui;
}
