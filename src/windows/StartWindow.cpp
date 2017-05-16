#include "StartWindow.h"
#include "ui_StartWindow.h"
#include <QDir>
#include <QFileDialog>
#include <ResultsDialog.h>
StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::StartWindow) {
  ui->setupUi(this);
//  this->setCentralWidget(ui->groupBox);
  this->showFullScreen();
  this->environment = new Game();
  connect(this, SIGNAL(updateWindow()), SLOT(updateContent()));
}

StartWindow::~StartWindow() { delete ui; }

void StartWindow::on_startBtn_clicked() {
  this->hide();
  this->show();
}

void StartWindow::on_resultsBtn_clicked() {
  this->hide();
  ResultsDialog res_d(environment);
  // if window was closing
  if (!res_d.exec()) {
  }
  this->show();
}

void StartWindow::updateContent() {}
