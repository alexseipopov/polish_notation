#include "s21_polish.h"

int s21_do_cos(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = cos((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_sin(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = sin((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_tan(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = tan((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_acos(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = acos((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_asin(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = asin((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_atan(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = atan((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_sqrt(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = sqrt((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_ln(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = log((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_log(s21_literal **numbers, s21_literal **operators) {
    int status = check_1_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = log10((*numbers)->data.value);
        transform_list_unar(data, numbers, operators);
    }
    return status;
}

int s21_do_plus(s21_literal **numbers, s21_literal **operators) {
    int status = check_2_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = ((*numbers)->next)->data.value + (*numbers)->data.value;
        transform_list_binar(data, numbers, operators);
    }
    return status;
}

int s21_do_minus(s21_literal **numbers, s21_literal **operators) {
    int status = check_2_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = ((*numbers)->next)->data.value - (*numbers)->data.value;
        transform_list_binar(data, numbers, operators);
    }
    return status;
}

int s21_do_div(s21_literal **numbers, s21_literal **operators) {
    int status = check_2_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = ((*numbers)->next)->data.value / (*numbers)->data.value;
        transform_list_binar(data, numbers, operators);
    }
    return status;
}

int s21_do_mult(s21_literal **numbers, s21_literal **operators) {
    int status = check_2_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value = ((*numbers)->next)->data.value * (*numbers)->data.value;
        transform_list_binar(data, numbers, operators);
    }
    return status;
}

int s21_do_mod(s21_literal **numbers, s21_literal **operators) {
    int status = check_2_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value =
            fmod(((*numbers)->next)->data.value, (*numbers)->data.value);
        transform_list_binar(data, numbers, operators);
    }
    return status;
}

int s21_do_pow(s21_literal **numbers, s21_literal **operators) {
    int status = check_2_values(*numbers);
    if (!status) {
        struct data data = {0};
        data.value =
            pow(((*numbers)->next)->data.value, (*numbers)->data.value);
        transform_list_binar(data, numbers, operators);
    }
    return status;
}

int open_bracket(s21_literal **numbers, s21_literal **operators) {
    int status = SUCCESS;
    struct data data = {0};
    if ((*numbers && *operators &&
         ((*numbers)->data.id > (*operators)->data.id)) ||
        (!*operators && *numbers)) {
        data.action = &s21_do_mult;
        data.priority = 2;
        status = push_operator_manager(data, numbers, operators);
    }
    data.priority = 0;
    *operators = s21_push(data, *operators);
    return status;
}

int close_bracket(s21_literal **numbers, s21_literal **operators) {
    int status = SUCCESS;
    while (*operators && ((*operators)->data.priority != 0) &&
           status == SUCCESS) {
        status = counter(numbers, operators);
    }
    if (*operators) {
        *operators = s21_pop(*operators);
        status = SUCCESS;
    } else {
        status = PARSING_ERROR;  // скобка не закрылась
    }
    return status;
}