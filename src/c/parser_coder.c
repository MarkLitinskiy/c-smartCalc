#include "s21_SmartCalc_v1.0.h"

/// @brief Прочёсывает строку и кодирует функции под односимвольные кодировки, а
/// также смотрит на корректность вводимой строки (разрешено ли вводить такие
/// символы). Если текущий символ - это первая буква одной из фукций, которую
/// нужно сократить, то срабатывает триггер и вызвается соответсвующая
/// процедура.
/// @param strIn сырая строка
/// @param strOut строка для вывода
/// @param allowVal массив разрешённых символов, которые могут встречаться
/// @return указатель на строку, которая получилась
char *parserCoder(char *strIn, char *strOut, char *X, int *error) {
  for (int i = 0, j = 0; strIn[i] != '\0'; i++, j++) {
    if (*error == OK) {
      *error = checkVal(strIn[i]);  // проверка, может ли быть такой символ
      switch (strIn[i]) {
        case 's':
          parserSinSqrt(strIn, strOut, &i, j, error);
          break;
        case 'c':
          parserCos(strIn, strOut, &i, j, error);
          break;
        case 't':
          parserTan(strIn, strOut, &i, j, error);
          break;
        case 'a':
          parserAsinAcosAtan(strIn, strOut, &i, j, error);
          break;
        case 'l':
          parserLogLn(strIn, strOut, &i, j, error);
          break;
        case 'm':
          parserMod(strIn, strOut, &i, j, error);
          break;
        case '-':
          parserUnarMin(strIn, strOut, &i, j);
          break;
        case '+':
          parserUnarPlus(strIn, strOut, &i, &j);
          break;
        case 'X':
          parserX(strOut, &j, X, error);
          break;
        default:
          strOut[j] = strIn[i];
          break;
      }
    } else {
      break;
    }
    if (strIn[i + 1] == '\0') {  // если строка закончилась
      strOut[j + 1] = '\0';
    }
  }
  return strOut;
}

/// @brief Проверочка является ли текущий символ допустимым, происходит
/// сравнение с массивом из допустимых символов allowVal
/// @param val Текущий символ
/// @return 0 - если всё хорошо, 1 - если символ не разрешён (код ошибки)
int checkVal(char val) {
  int i = 0;
  char allowVal[28] = {'s', 'c', 't', 'a', 'l', 'm', '+', '-', '*', '/',
                       '^', '(', ')', '1', '2', '3', '4', '5', '6', '7',
                       '8', '9', '0', '.', 'X', 'e', 'P', '\0'};
  int flag = -1;
  while (allowVal[i] != '\0') {
    if (val == allowVal[i]) flag = OK;
    i++;
  }
  return flag;
}

/*
  Вспомогательные процедуры парсера-кодера:
  Если в строке встречается первая буква функции - вызвается вспомогательная
  процедура, которая проверяет последующие символы. Если они совпадают с
  названием функции, она кодируется, если нет - ошибка. Функции с одинаковой
  первой буквой объединены
*/
// НУЖНО ДОБАВИТЬ ПРОВЕРКУ НА ТО, ЧТО В СТРОКЕ ПРИ СЧИТЫВАНИИ СЛЕДУЮЩИХ
// ЭЛЕМЕНТОВ ЧТО-ТО ЕСТЬ, ЧТОБЫ НЕ ВЫХОДИТ ЗА ГРАНИЦЫ МАССИВА И НЕ ПОЛУЧИТЬ
// УТЕЧКИ, ПРИМЕР: "sin(60)+at" или "tan(30)+si"
// (Но их почему-то нет)

void parserSinSqrt(char *strIn, char *strOut, int *i, int j, int *error) {
  if (strIn[*i] != '\0' && strIn[*i + 1] == 'i' && strIn[*i + 2] == 'n') {
    strOut[j] = 's';
    *i = *i + 2;
  } else {
    if (strIn[*i] != '\0' && strIn[*i + 1] == 'q' && strIn[*i + 2] == 'r' &&
        strIn[*i + 3] == 't') {
      strOut[j] = 'q';
      *i = *i + 3;
    } else {
      *error = 1;  // Ошибка ввода sin/sqrt
      strOut[0] = '\0';
    }
  }
}
void parserCos(char *strIn, char *strOut, int *i, int j, int *error) {
  if (strIn[*i] != '\0' && strIn[*i + 1] == 'o' && strIn[*i + 2] == 's') {
    strOut[j] = 'c';
    *i = *i + 2;
  } else {
    *error = 2;  // Ошибка ввода cos
    strOut[0] = '\0';
  }
}
void parserTan(char *strIn, char *strOut, int *i, int j, int *error) {
  if (strIn[*i] != '\0' && strIn[*i + 1] == 'a' && strIn[*i + 2] == 'n') {
    strOut[j] = 't';
    *i = *i + 2;
  } else {
    *error = 3;  // Ошибка ввода tan
    strOut[0] = '\0';
  }
}
void parserAsinAcosAtan(char *strIn, char *strOut, int *i, int j, int *error) {
  if (strIn[*i] != '\0' && strIn[*i + 1] == 's' && strIn[*i + 2] == 'i' &&
      strIn[*i + 3] == 'n') {
    strOut[j] = 'y';
    *i = *i + 3;
  } else {
    if (strIn[*i] != '\0' && strIn[*i + 1] == 'c' && strIn[*i + 2] == 'o' &&
        strIn[*i + 3] == 's') {
      strOut[j] = 'u';
      *i = *i + 3;
    } else {
      if (strIn[*i] != '\0' && strIn[*i + 1] == 't' && strIn[*i + 2] == 'a' &&
          strIn[*i + 3] == 'n') {
        strOut[j] = 'i';
        *i = *i + 3;
      } else {
        *error = 4;  // Ошибка ввода asin/acos/atan
        strOut[0] = '\0';
      }
    }
  }
}
void parserLogLn(char *strIn, char *strOut, int *i, int j, int *error) {
  if (strIn[*i] != '\0' && strIn[*i + 1] == 'o' && strIn[*i + 2] == 'g') {
    strOut[j] = 'g';
    *i = *i + 2;
  } else {
    if (strIn[*i] != '\0' && strIn[*i + 1] == 'n') {
      strOut[j] = 'n';
      *i = *i + 1;
    } else {
      *error = 5;  // Ошибка ввода log/ln
      strOut[0] = '\0';
    }
  }
}
void parserMod(char *strIn, char *strOut, int *i, int j, int *error) {
  if (strIn[*i] != '\0' && strIn[*i + 1] == 'o' && strIn[*i + 2] == 'd') {
    strOut[j] = 'm';
    *i = *i + 2;
  } else {
    *error = 6;  // Ошибка ввода mod
    strOut[0] = '\0';
  }
}
void parserUnarMin(char *strIn, char *strOut, int *i, int j) {
  if (*i == 0 || (*i != 0 && strIn[*i - 1] == '(')) {
    strOut[j] = '~';
  } else {
    strOut[j] = '-';
  }
}
void parserUnarPlus(char *strIn, char *strOut, int *i, int *j) {
  if (*i == 0 || (*i != 0 && strIn[*i - 1] == '(')) {
    strOut[*j] = '@';
  } else {
    strOut[*j] = '+';
  }
}
void parserX(char *strOut, int *j, char *X, int *error) {
  if (X[0] == '-') {
    X[0] = '~';
  }
  if (X[0] == '\0') {
    *error = 7;  // X не задан!
  } else {
    for (int k = 0; X[k] != '\0'; k++) {
      strOut[*j] = X[k];
      (*j)++;
    }
    (*j)--;
  }
}
