#include "s21_polish.h"

void do_nothing(s21_literal *first, s21_literal *second) { printf("Im work\n"); }

void s21_do_cos(s21_literal **numbers, s21_literal **operators) {
    // оператор унарный - беру последний элемент из чисел и вычисляю под него, далее убираю последний оператор
    struct data data = {0};
    data.value = cos(*numbers->data.value);
    *numbers = s21_pop(*numbers);
}