#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>

extern "C" {
#include "c/creditCalculation/creditCalculation.h"
}

namespace Ui {
class creditWindow;
}

class creditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit creditWindow(QWidget *parent = nullptr);
  ~creditWindow();

 private slots:
  void on_pushButton_result_clicked();

 private:
  Ui::creditWindow *ui;
  void resetInputData();
  void annuitentCalculation();
  void differentCalculation();
  double sumCredit = 0;
  int monthTerm = 0;
  double interestRate = 0;
  double overpayment = 0;
  double totalPay = 0;
  int statePay = 0;
};

#endif  // CREDITWINDOW_H
