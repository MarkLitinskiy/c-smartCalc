#ifndef __DEPOSIT_CALCULATION__
#define __DEPOSIT_CALCULATION__
#include <math.h>
double depositCalc(double sumDeposit, int monthTerm, double interestRate,
                   double nalogRate, int period, int capital, int refillCount,
                   int refill, int withdrawalCount, int withdrawal,
                   double *sumPercent, double *sumNalog);
#endif  // __DEPOSIT_CALCULATION__