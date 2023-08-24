#include "s21_SmartCalc_v1.0.h"
/// @brief Раскидывает строку strOut по двум стекам - в первый числа, во второй
/// все остальные символы. Вычисление проходит параллельно записи в функции
/// polishCalculate, поэтому в результате работы функции стек с операторами
/// пустой, а в стеке с числами остаётся одно число, которое является ответом.
/// Унарный минус выполняется сразу и не добавляется в стек
/// @param strOut Закодированная строка, которую раскидываем
/// @param numbersStack Стек с числами
/// @param symStack Стек с лексемами
void parserOfStacks(char *strOut, stack **numbersStack, stack **symStack) {
  for (int i = 0; strOut[i] != '\0'; i++) {
    if (isNumberDot(strOut[i]) == 1) {
      pushStack(numbersStack, parserNumber(strOut, &i), '\0');
    } else if (isNumberDot(strOut[i]) == 0) {
      polshCalculate(strOut[i], numbersStack, symStack);
    } else if (isNumberDot(strOut[i]) == 3 &&
               strOut[i] == 'P') {  // для константы PI
      pushStack(numbersStack, PI, '\0');
    } else if (isNumberDot(strOut[i]) == 3 &&
               strOut[i] == 'e') {  // для константы E
      pushStack(numbersStack, E, '\0');
    }
  }
  while (*symStack != NULL) {  // Если строка закончилась, а в стеке операторов
                               // ещё есть значения
    polshCalculate('\0', numbersStack, symStack);
  }
}

/// @brief Вызавается когда начинается число, функция считывает это число в
/// double, а также сдвигает счётчик в исследуемой строке на позицию после числа
/// @param strOut Указатель на строку
/// @param i Счётчик текущего положения в strOut
/// @return Найденное число
double parserNumber(char *strOut, int *i) {
  double res = 0;
  int dotFlag = 0;  // флаг, что началась дробная часть
  int drobrazr = 1;  // счётчик дробных разрядов

  while (isNumberDot(strOut[*i]) != 0) {
    if (isNumberDot(strOut[*i]) == 1) {
      if (dotFlag == 0) {
        res = (res * 10) + (strOut[*i] - '0');
      } else {  // для дробной части
        res = res + (((double)(strOut[*i] - '0')) / (pow(10, drobrazr)));
        drobrazr++;
      }
    }
    if (isNumberDot(strOut[*i]) == 2) {
      dotFlag = 1;
    }
    (*i)++;
  }
  *i = *i - 1;
  return res;
}

/// @brief Определяет является ли символ цифрой, точкой или ни тем, ни другим
/// @param n Исследуемый символ
/// @return 0 - если оператор, 1 - если цифра, 2 - если точка, 3 - если
/// константа или X
int isNumberDot(char n) {
  int flag = 0;
  if (n >= 48 && n <= 57) {
    flag = 1;
  } else if (n == '.') {
    flag = 2;
  } else if (n == 'X' || n == 'P' || n == 'e') {
    flag = 3;
  }
  return flag;
}
