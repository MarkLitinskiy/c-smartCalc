#ifndef __S21_SMART_CALC_v1_0__
#define __S21_SMART_CALC_v1_0__
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERR 1
#define PI 3.1415926535897932384626433832795028841971
#define E 2.7182818284590452353602874713526624977572

typedef struct stack {
  char sym;
  double number;
  struct stack *next;
} stack;

typedef struct errorsVariables {
  int countBeginBrackets;
  int countEndBrackets;
  int dotFlag;

} errorsVariables;

/*
  Сокращения функций:
  sin - s
  cos - c
  tan - t
  asin - y
  acos - u
  atan - i
  sqrt - q
  ln - n
  log - g
  mod - m
  unar- - ~
  unar+ - @
*/

double calculation(char *strIn, char *X, int *error);
void allocateSpace(char **str);
void freeSpace(char **str);

// функции работы со стеком
void pushStack(stack **top, double number, char sym);
void popStack(stack **top);
void printStack(stack *top);
void freeStack(stack **top);

// функции кодировщика входной строки
char *parserCoder(char *strIn, char *strOut, char *X, int *error);
int checkVal(char val);
void parserSinSqrt(char *strIn, char *strOut, int *i, int j, int *error);
void parserCos(char *strIn, char *strOut, int *i, int j, int *error);
void parserTan(char *strIn, char *strOut, int *i, int j, int *error);
void parserAsinAcosAtan(char *strIn, char *strOut, int *i, int j, int *error);
void parserLogLn(char *strIn, char *strOut, int *i, int j, int *error);
void parserMod(char *strIn, char *strOut, int *i, int j, int *error);
void parserUnarMin(char *strIn, char *strOut, int *i, int j);
void parserUnarPlus(char *strIn, char *strOut, int *i, int *j);
void parserX(char *strOut, int *j, char *X, int *error);

// парсинг строки по стекам
void parserOfStacks(char *strOut, stack **numbersStack, stack **symStack);
int isNumberDot(char n);
double parserNumber(char *strOut, int *i);

// функции счёта польской нотации
void polshCalculate(char sym, stack **numbersStack, stack **symStack);
int findPriority(char sym);
double doubleOperation(double lastNumber, double preLastNumber, char operation);
double unarOperation(double lastNumber, char operation);
void stackUnarOperation(stack **numbersStack, stack **symStack);
void stackDoubleOperation(stack **numbersStack, stack **symStack);
double s21_fmod(double x, double y);

// проверка входной строки на математические ошибки
int mathCheckStr(char *str);
#endif  // __S21_SMART_CALC_v1_0__
