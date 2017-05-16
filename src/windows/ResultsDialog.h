#ifndef RESULTSDIALOG_H
#define RESULTSDIALOG_H

#include <QDialog>
#include <Game.h>
#include <User.h>
namespace Ui {
class ResultsDialog;
}

class ResultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsDialog(Game * game,QWidget *parent = 0);
    ~ResultsDialog();

private:
    Ui::ResultsDialog *ui;
    Game * environment;
};

#endif // RESULTSDIALOG_H
