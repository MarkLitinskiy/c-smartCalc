#include "c/s21_SmartCalc_v1.0.h"
int main() {
  stack *numbersStack = {0};
  stack *symStack = {0};

  char strOut[] =
      "acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)+4*(-10)";
  int error = 0;

  calculation(strOut, "", &error);

  freeStack(&numbersStack);
  freeStack(&symStack);
  return 0;
}