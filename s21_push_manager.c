#include "s21_polish.h"

int push_operator_manager(struct data data, s21_literal **numbers,
                          s21_literal **operators) {
    int status = SUCCESS;
    // static int last_type = 0;
    if (data.priority == 0) {
        status = data.action(numbers, operators);
    } else {
        while (*operators && ((*operators)->data.priority > data.priority)) {
            status = (*operators)->data.action(numbers, operators);
        }
        *operators = s21_push(data, *operators);
    }
    return status;
}

int counter(s21_literal **numbers, s21_literal **operators) {
    int status = SUCCESS;
    status = (*operators)->data.action(numbers, operators);
    return status;
}