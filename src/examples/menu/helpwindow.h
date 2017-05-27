#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QWidget
{
    Q_OBJECT

signals:
    void mainWindow();

public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();

private slots:
    void on_backPushButton_clicked();

private:
    Ui::HelpWindow *ui;
};

#endif // HELPWINDOW_H
