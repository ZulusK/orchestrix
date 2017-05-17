#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QDateTime>
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow:: makePlot();

}

MainWindow::~MainWindow()
{
    delete ui;
}
//Find min value
int findMin(int min,int count,QVector<double>x) {
    for (int i = 0; i < count;i++) {
        if(x[i] < min) {
            min = x[i];
        }

     }
    return min;
}
//Find max value
int findMax(int max,int count,QVector<double>x) {
    for (int i = 0; i < count;i++) {
        if (x[i] > max) {
            max = x[i];
        }

     }
    return max;
}

int  MainWindow:: makePlot() {
    QString filePath(":/doc/mus.csv");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
          qDebug() << file.errorString();
          return 1;
     }
    int N = 21474836;
    QVector<double> x(N), y(N);
    QStringList xCoordinates;
    QStringList yCoordinates;
    int i = 0;
    int count = 0;
    while (!file.atEnd()) {
            QByteArray line = file.readLine();
            xCoordinates.append(line.split(',').first());
            QString strX = xCoordinates[i];
            x[i] = strX.toInt();
            yCoordinates.append(line.split(',').last());
            QString strY = yCoordinates[i];
            strY.remove(QChar('\n'));
            y[i] = strY.toInt();
            i++;
            count++;
    }

    file.close();


    int max_X = -1;
    int min_X = 2147483647;
    max_X = findMax(max_X,count,x);
    min_X = findMin(min_X,count,x);
    qDebug()<< findMax(max_X,count,x);
    qDebug()<< findMin(min_X,count,x);
    int max_Y = -1;
    int min_Y = 2147483647;
    max_Y = findMax(max_Y,count,y);
    min_Y = findMin(min_Y,count,y);
    qDebug()<< findMax(max_Y,count,y);
    qDebug()<< findMin(min_Y,count,y);
    // cоздаем график и добавляем данные:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->yAxis->setVisible(true);
    ui->customPlot->yAxis->setTicks(false);
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    ui->customPlot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси
    // задаем имена осей координат
//    ui->customPlot->xAxis->setLabel("x");
//    ui->customPlot->yAxis->setLabel("y");
    // задаем размеры осей
    ui->customPlot->xAxis->setRange(min_X, max_X);
    ui->customPlot->yAxis->setRange(min_Y,max_Y);
   // ui->customPlot->axisRect()->setBackground(Qt::gray);



    return 0;
}



void MainWindow::on_ExitPushButton_clicked()
{

}
