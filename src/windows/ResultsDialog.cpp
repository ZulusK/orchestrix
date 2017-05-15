#include "ResultsDialog.h"
#include "ui_ResultsDialog.h"

ResultsDialog::ResultsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultsDialog)
{
    ui->setupUi(this);
}

ResultsDialog::~ResultsDialog()
{
    delete ui;
}
