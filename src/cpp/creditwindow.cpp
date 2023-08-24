#include "cpp/creditwindow.h"

#include <iostream>

#include "QtWidgets/qtablewidget.h"
#include "c/creditCalculation/creditCalculation.h"
#include "ui_creditwindow.h"

creditWindow::creditWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::creditWindow) {
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна
}

creditWindow::~creditWindow() { delete ui; }

void creditWindow::on_pushButton_result_clicked() {
  resetInputData();
  if (ui->radioButton_annuitent->isChecked()) {  // определение типа
    annuitentCalculation();
  }
  if (ui->radioButton_different->isChecked()) {
    differentCalculation();
  }
}

void creditWindow::resetInputData() {  // для обновления значений всех
                                       // переменных
  sumCredit = ui->spinBox_sumCredit->text().toDouble();
  monthTerm = ui->spinBox_monthTerm->text().toInt();
  interestRate = (ui->doubleSpinBox_interestRate->text().toDouble()) / 100 / 12;
  overpayment = 0;
  totalPay = 0;
  statePay = 0;
}

void creditWindow::annuitentCalculation() {
  ui->tableWidget_monthlyPayment->setRowCount(
      monthTerm);  // задаём параметры таблицы
  ui->tableWidget_monthlyPayment->setColumnCount(1);
  ui->tableWidget_monthlyPayment->setHorizontalHeaderLabels(QStringList()
                                                            << "Сумма выплаты");
  for (int i = 0; i < monthTerm; i++) {  // расчёт ежемесячных выплат
    QTableWidgetItem *tbl = new QTableWidgetItem(QString::number(
        creditAnnuitentCalculation(sumCredit, monthTerm, interestRate,
                                   &overpayment, &totalPay),
        'f', 3));
    ui->tableWidget_monthlyPayment->setItem(0, i, tbl);
  }
  ui->lineEdit_overpayment->setText(QString::number(overpayment, 'f', 3));
  ui->lineEdit_totalPay->setText(QString::number(totalPay, 'f', 3));
}

void creditWindow::differentCalculation() {
  statePay = monthTerm - 1;
  ui->tableWidget_monthlyPayment->setRowCount(
      monthTerm);  // задаём параметры таблицы
  ui->tableWidget_monthlyPayment->setColumnCount(1);
  ui->tableWidget_monthlyPayment->setHorizontalHeaderLabels(QStringList()
                                                            << "Сумма выплаты");
  for (int i = monthTerm - 1; i >= 0; i--) {  // расчёт ежемесячных выплат

    QTableWidgetItem *tbl = new QTableWidgetItem(QString::number(
        creditDifferentCalculation(sumCredit, monthTerm, &statePay,
                                   interestRate, &overpayment, &totalPay),
        'f', 3));
    ui->tableWidget_monthlyPayment->setItem(0, i, tbl);
  }
  if (monthTerm != 0) overpayment = overpayment - sumCredit;

  ui->lineEdit_overpayment->setText(QString::number(overpayment, 'f', 3));
  ui->lineEdit_totalPay->setText(QString::number(totalPay, 'f', 3));
}
