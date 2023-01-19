#include "s21_polish.h"

int unar_action(unit **numbers, unit **operators, double (*action)(double)) {
    int status = check_1_values(*numbers);
    if (status == HAVE_VAR) {
        *numbers = s21_push((*operators)->data, *numbers);
        *operators = s21_pop(*operators);
        status = SUCCESS;
    } else if (status == SUCCESS) {
        struct data data = {0};
        data.value = action((*numbers)->data.value);
        data.type = NUM;
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int binar_action(unit **numbers, unit **operators,
                 double (*action)(double, double)) {
    int status = check_2_values(*numbers);
    if (status == HAVE_VAR) {
        *numbers = s21_push((*operators)->data, *numbers);
        *operators = s21_pop(*operators);
        status = SUCCESS;
    } else if (status == SUCCESS) {
        struct data data = {0};
        data.value =
            action(((*numbers)->next)->data.value, (*numbers)->data.value);
        data.type = NUM;
        transform_list_binar(data, numbers, operators);
    }
    return status;
}
