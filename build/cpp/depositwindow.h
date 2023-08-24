#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDialog>

extern "C" {
#include "c/depositCalculation/depositCalculation.h"
}

namespace Ui {
class depositWindow;
}

class depositWindow : public QDialog {
  Q_OBJECT

 public:
  explicit depositWindow(QWidget *parent = nullptr);
  ~depositWindow();

 private:
  Ui::depositWindow *ui;
  void resetInputData();
  double sumDeposit = 0;
  int monthTerm = 0;
  double interestRate = 0;
  double nalogRate = 0;
  int period = 0;
  int capital = 0;
  int refillCount = 0;
  int refill = 0;
  int withdrawalCount = 0;
  int withdrawal = 0;
  double sumPercent = 0;
  double sumNalog = 0;
 private slots:
  void on_pushButton_clicked();
};

#endif  // DEPOSITWINDOW_H
