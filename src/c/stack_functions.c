#include "s21_SmartCalc_v1.0.h"

/// @brief Функция для добавления узла в стек
/// @param top Указатель на текущий последний элемент стека (двойной, чтобы
/// можно было изменять)
/// @param number Если данные числовые
/// @param sym Если данные знаковые
void pushStack(stack **top, double number, char sym) {
  stack *current =
      (stack *)malloc(sizeof(stack));  // выделяется память под узел стека
  if (current == NULL) {
    exit(1);
  }
  current->sym = sym;
  current->number = number;
  current->next = NULL;
  if (*top == NULL) {  // Если создаётся первый элемент
    *top = current;  // последним элементом стека становится текущий
  } else {
    current->next = *top;  // новый узел стека становится последним
    *top = current;
  }
}

/// @brief Функция для чтения и удаления последнего узла стека
/// @param top Указатель на текущий последний элемент стека (двойной, чтобы
/// можно было изменять)
void popStack(stack **top) {
  stack *temporaryElem = {0};
  if (top == NULL) {  // Если стек пустой
    return;
  }
  temporaryElem = *top;
  *top =
      (*top)->next;  // указатель последнего узла подвязывается на предпоследний
  free(temporaryElem);
}

void freeStack(stack **top) {  // освобождение памяти стека
  while (*top != NULL) {
    popStack(top);
  }
}