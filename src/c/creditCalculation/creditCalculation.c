#include "creditCalculation.h"

#include <math.h>
/// @brief Кредитный аннуитентный калькулятор
/// @param sumCredit Общая сумма кредита
/// @param monthTerm Срок в месяцах
/// @param interestRate Процентная ставка
/// @param overpayment Переплата по кредиту
/// @param totalPay Общая выплата
/// @return Ежемесячный платёж
double creditAnnuitentCalculation(double sumCredit, int monthTerm,
                                  double interestRate, double *overpayment,
                                  double *totalPay) {
  double monthlyPayment = 0;

  if(interestRate != 0){
  monthlyPayment = sumCredit *
                   ((interestRate * pow((1 + interestRate), monthTerm)) /
                   (pow((1 + interestRate), monthTerm) - 1));
  } else {
      monthlyPayment = sumCredit/monthTerm;
  }

  *overpayment = (monthTerm * monthlyPayment) - sumCredit;
  *totalPay = monthlyPayment * monthTerm;
  return monthlyPayment;
}

/// @brief Кредитный дифференцируемый калькулятор, должен вызываться по
/// количеству платежей
/// @param sumCredit Общая сумма кредита
/// @param monthTerm Срок в месяцах
/// @param statePay Сколько осталось платежей (изначально равно сроку в месяцах)
/// @param interestRate Процентная ставка
/// @param overpayment Переплата по кредиту
/// @param totalPay Общая выплата
/// @return Ежемесячный платёж по текущему месяцу
double creditDifferentCalculation(double sumCredit, int monthTerm,
                                  int *statePay, double interestRate,
                                  double *overpayment, double *totalPay) {
  double monthlyPayment = 0;

  double balanceOfDebt = sumCredit - (sumCredit / monthTerm * (*statePay));
  monthlyPayment =
      (sumCredit / monthTerm) + (balanceOfDebt * interestRate);

  *totalPay = *totalPay + monthlyPayment;
  *overpayment =
      *overpayment +
      monthlyPayment;  // После цикла вычитается сумма кредита
  (*statePay)--;
  return monthlyPayment;
}
