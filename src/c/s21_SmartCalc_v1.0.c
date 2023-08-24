#include "s21_SmartCalc_v1.0.h"

/// @brief Связующая функция между фронтом и бэком. Передаёт входную строку в
/// кодирующую функцию, проверяет строку на мат. ошибки, распарсивает по стекам,
/// считает через польскую нотацию и записывает результать в переменную result
/// @param strIn входная строка
/// @param X значение переменной X
/// @param error для кода ошибки, 0 - если всё хорошо
/// @return результат вычислений
double calculation(char *strIn, char *X, int *error) {
  stack *numbersStack = {0};
  stack *symStack = {0};
  char *strOut = {0};
  double result = 0;
  allocateSpace(&strOut);
  if (X[0] != '\0') {
    for (int i = 0; X[i] != '\0'; i++) {
      if (isNumberDot(X[i]) != 1 && isNumberDot(X[i]) != 2 && X[i] != '-' &&
          X[i] != '+')
        *error = 18;  // Некорректно задан X!
    }
  }

  if (*error == 0) strOut = parserCoder(strIn, strOut, X, error);
  if (*error == 0) *error = mathCheckStr(strOut);
  if (*error == 0) parserOfStacks(strOut, &numbersStack, &symStack);
  if ((numbersStack != NULL && numbersStack->next != NULL) ||
      symStack != NULL) {
    *error = 17;  // Ошибка в выражении!
  }
  if (*error == 0 && numbersStack != NULL) result = numbersStack->number;
  freeSpace(&strOut);
  freeStack(&numbersStack);
  freeStack(&symStack);
  return result;
}

/// @brief Выделение памяти для строк
/// @param str Указатель на строку, которой выделяется место ()
/// @return Указатель на строку, которой выделяется место
void allocateSpace(char **str) {
  *str = (char *)calloc(257, sizeof(char));

  if (*str == NULL) {  // проверочка выделилась ли память
    exit(1);
  }
}

/// @brief Освобождение памяти строки
/// @param str Указатель на строку
void freeSpace(char **str) {
  if (str != NULL) free(*str);
}
