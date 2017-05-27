#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scorewindow.h"
#include "startwindow.h"
#include "helpwindow.h"
#include "player.h"
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_setScorePushButton_clicked();

    void on_startPushButton_clicked();

    void on_helpPushButton_clicked();

    void on_exitPushButton_clicked();

    void on_signUpPushButton_clicked();

    void on_logInPushButton_clicked();

private:
    Ui::MainWindow *ui;
    StartWindow *startWindow;
    ScoreWindow *scoreWindow;
    HelpWindow *helpWindow;

};

#endif // MAINWINDOW_H
