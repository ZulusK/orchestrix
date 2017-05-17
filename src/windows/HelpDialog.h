#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <Game.h>
#include <User.h>
namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(Game * game,QWidget *parent = 0);
    ~HelpDialog();

private:
    Ui::HelpDialog *ui;
    Game * environment;
};

#endif // HELPDIALOG_H
