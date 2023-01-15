#include "s21_polish.h"

int push_operator_manager(struct data data, s21_literal **numbers,
                          s21_literal **operators) {
    int status = SUCCESS;
    int is_close_bracket = 0;
    if (data.priority == 0) {
        status = data.action(numbers, operators);
        is_close_bracket = 1;
    }
    while (*operators && ((*operators)->data.priority > data.priority)) {
        status = (*operators)->data.action(numbers, operators);
    }
    if (is_close_bracket) {
        *operators = s21_push(data, *operators);
    }
    return status;
}

int counter(s21_literal **numbers, s21_literal **operators) {
    int status = SUCCESS;
    status = (*operators)->data.action(numbers, operators);
    return status;
}