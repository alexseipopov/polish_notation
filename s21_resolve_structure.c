#include "s21_polish.h"

int parse_element(unit *numbers, unit **result, unit **stack, double variable) {
    int status = SUCCESS;
    if (numbers->data.type == NUM) {
        *result = s21_push(numbers->data, *result);
    } else if (numbers->data.type == VAR) {
        numbers->data.value = variable;
        numbers->data.type = NUM;
        *result = s21_push(numbers->data, *result);
    } else {
        status = check_possible_push(numbers->data, stack);
        if (status == NEED_UNSTACK)
            status = unstack(numbers->data, result, stack);
        if (status == SUCCESS) *stack = s21_push(numbers->data, *stack);
    }
    return status;
}

int resolve_struct(unit **numbers, double variable, double *res) {
    int status = SUCCESS;
    unit *result = NULL;
    unit *stack = NULL;
    while (*numbers && status == SUCCESS) {
        status = parse_element(*numbers, &result, &stack, variable);
        *numbers = s21_pop(*numbers);
    }
    if (result && status == SUCCESS) {
        // status = resolve_lists(&result, &stack);
        while (stack && status == SUCCESS) {
            status = stack->data.action(&result, &stack);
        }
        *res = result->data.value;
        result = s21_pop(result);
    }
    // print_stack(result);
    return status;
}