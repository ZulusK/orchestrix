#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../EqOrch/equalizer.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    Equalizer * eq;
    int startArray[24];


    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();


private slots:
    void iterate();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
