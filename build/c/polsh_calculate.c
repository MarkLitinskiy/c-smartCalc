#include "s21_SmartCalc_v1.0.h"

/// @brief Добавление в стек операторов новых элементов, а также их исполнение.
/// Если в стеке операторов нет элементов или текущий оператор - открывающая
/// скобка, просто записываем в стек. В ином случае - смотрим на приоритет
/// текущей операции. Если он <= приоритету последней операции в стеке, то
/// проводим операции в стеке, пока это условие истинно, а затем записываем
/// текущий оператор в стек.
/// @param sym текущий оператор, если \0, значит строка закончилась, и считаем
/// всё оставшееся в стеке операторов
/// @param numbersStack стек чисел
/// @param symStack стек операторов
void polshCalculate(char sym, stack **numbersStack, stack **symStack) {
  if (*symStack == NULL || sym == '(') {
    pushStack(symStack, 0, sym);
  } else {
    if ((findPriority(sym) <= findPriority((*symStack)->sym) || sym == '\0') &&
        sym != ')') {
      do {
        if ((sym == '^' && ((*symStack)->sym) == '^'))
          continue;  // если две степени идут подряд, нужно чтобы вторая не
                     // считалась, а записывалась в стек до момента, пока
                     // степени не закончатся, только затем вынимаем степени по
                     // одной и вычисляем

        if (findPriority((*symStack)->sym) == 4) {
          stackUnarOperation(numbersStack, symStack);
        } else {
          stackDoubleOperation(numbersStack, symStack);
        }
      } while ((*symStack) != NULL &&
               findPriority(sym) <= findPriority((*symStack)->sym) &&
               sym != '^');  // повторяем пока приоритет текущего оператора <=
                             // последнему в стеке, но ^ считаются справа
                             // налево, поэтому исключение
      if (sym != '\0')
        pushStack(symStack, 0, sym);  // кладём текущий оператор в стек только
                                      // пока строка не закончилась
    } else {
      if (sym == ')') {  // встретили закрытую скобку
        while ((*symStack)->sym !=
               '(') {  // выполняем операции, пока не встретим открывающую
          if (findPriority((*symStack)->sym) == 4) {
            stackUnarOperation(numbersStack, symStack);
          } else {
            stackDoubleOperation(numbersStack, symStack);
          }
        }
        popStack(symStack);  // удаление открывающей скобки
        if ((*symStack) != NULL &&
            (*symStack)->sym ==
                '~') {  // если перед скобкой стоял унарный минус
          (*numbersStack)->number = ((*numbersStack)->number) * (-1);
          popStack(symStack);  // удаление унарного минуса
        }
      } else {
        pushStack(symStack, 0,
                  sym);  // если приоритет текущего оператора > последнего в
                         // стеке, просто его добавляем в стек
      }
    }
  }
}

/// @brief Процедура работы со стеком при осуществлении унарной операции:
/// вытаскиваем последнее число из стека чисел, проводим с ним унарную операцию,
/// удаляем операцию из стека операций, кладём результат в стек с числами
/// @param numbersStack стек с числами
/// @param symStack стек с операциями
void stackUnarOperation(stack **numbersStack, stack **symStack) {
  double lastNumber = 0;
  lastNumber = (*numbersStack)->number;
  popStack(numbersStack);
  lastNumber = unarOperation(lastNumber, (*symStack)->sym);
  popStack(symStack);
  pushStack(numbersStack, lastNumber, '\0');
}

/// @brief Процедура работы со стеком при осуществлении арифметической операции
/// с двумя аргументами: вытаскиваем последние два числа из стека чисел,
/// проводим с ними арифметическую операцию, удаляем операцию из стека операций,
/// кладём результат в стек с числами
/// @param numbersStack стек с числами
/// @param symStack стек с операциями
void stackDoubleOperation(stack **numbersStack, stack **symStack) {
  double lastNumber = 0, preLastNumber = 0;
  lastNumber = (*numbersStack)->number;
  popStack(numbersStack);
  preLastNumber = (*numbersStack)->number;
  popStack(numbersStack);
  lastNumber = doubleOperation(lastNumber, preLastNumber, (*symStack)->sym);
  popStack(symStack);
  pushStack(numbersStack, lastNumber, '\0');
}

/// @brief Вычисление арифметических операция с двумя аргументами
/// @param lastNumber второй аргумент
/// @param preLastNumber первый аргумент
/// @param operation вид арифметической операции
/// @return результат
double doubleOperation(double lastNumber, double preLastNumber,
                       char operation) {
  double res = 0;
  switch (operation) {
    case '+':
      res = lastNumber + preLastNumber;
      break;
    case '-':
      res = preLastNumber - lastNumber;
      break;
    case '*':
      res = preLastNumber * lastNumber;
      break;
    case '/':
      res = preLastNumber / lastNumber;
      break;
    case '^':
      res = pow(preLastNumber, lastNumber);
      break;
    case 'm':
      res = s21_fmod(preLastNumber, lastNumber);
      break;
  }
  return res;
}

/// @brief Вычисление унарных функций
/// @param arg аргумент функции
/// @param operation сама функция
/// @return результат функции
double unarOperation(double arg, char operation) {
  double res = 0;
  switch (operation) {
    case 's':
      res = sin(arg);
      break;
    case 'c':
      res = cos(arg);
      break;
    case 't':
      res = tan(arg);
      break;
    case 'y':
      res = asin(arg);
      break;
    case 'u':
      res = acos(arg);
      break;
    case 'i':
      res = atan(arg);
      break;
    case 'q':
      res = sqrt(arg);
      break;
    case 'n':
      res = log(arg);
      break;
    case 'g':
      res = log10(arg);
      break;
    case '~':
      res = arg * (-1);
      break;
    case '@':
      res = arg;
      break;
  }
  return res;
}

/// @brief Функция ищет приоритет какой-либо операции, они записаны подряд в
/// массиве char
/// @param sym оператор
/// @return его приоритет
int findPriority(char sym) {
  char result = '0';
  char priority[40] = {'+', '-', '*', '/', '^', 'm', '~', '@', 's', 'c',
                       't', 'y', 'u', 'i', 'q', 'n', 'g', '(', ')', 'x',
                       '1', '1', '2', '2', '3', '2', '4', '4', '4', '4',
                       '4', '4', '4', '4', '4', '4', '4', '0', '0', '7'};
  for (int i = 0; i <= 19; i++) {
    if (sym == priority[i]) result = priority[i + 20];
  }
  return result - '0';
}

double s21_fmod(double x, double y) {
  double result;

  if (y == 0.0) {
    result = (0.0 / 0.0);
  } else if (y == (1.0 / 0.0) || y == (-1.0 / 0.0)) {
    result = x;
  } else {
    if (x / y < 0) {
      result = x - ceil(x / y) * y;
    } else {
      result = x - floor(x / y) * y;
    }
  }
  return result;
}
