#ifndef RESULTSDIALOG_H
#define RESULTSDIALOG_H

#include <Game.h>
#include <QDialog>
#include <User.h>
#include <vector>
namespace Ui {
class ResultsDialog;
}

class ResultsDialog : public QDialog {
  Q_OBJECT

public:
  explicit ResultsDialog(Game *game, QWidget *parent = 0);
  ~ResultsDialog();

    void load(const QString &jsonStr);
private:
  Ui::ResultsDialog *ui;
  Game *environment;
  void drawTable();
};

#endif // RESULTSDIALOG_H
