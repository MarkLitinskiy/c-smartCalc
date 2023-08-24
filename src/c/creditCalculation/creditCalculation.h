#ifndef __CREDIT_CALCULATION__
#define __CREDIT_CALCULATION__
#include <math.h>

double creditAnnuitentCalculation(double sumCredit, int monthTerm,
                                  double interestRate, double *overpayment,
                                  double *totalPay);
double creditDifferentCalculation(double sumCredit, int monthTerm,
                                  int *statePay, double interestRate,
                                  double *overpayment, double *totalPay);

#endif  // __CREDIT_CALCULATION__
