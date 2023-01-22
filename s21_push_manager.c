#include "s21_polish.h"

int push_number(struct data data, unit **numbers, int last_type) {
    int status = SUCCESS;
    if (last_type == NUM) {
        status = FORGOT_OPERATOR;
    } else if (last_type == BRC) {
        status = MISSING_OPERATOR;
    } else if (last_type == VAR) {
        status = CHANGE_VAR_POSITION;
    } else {
        *numbers = s21_push(data, *numbers);
    }
    return status;
}

int push_open_bracket(struct data data, unit **numbers, unit **operators,
                      int last_type) {
    int status = SUCCESS;
    if (last_type == NUM || last_type == VAR || last_type == BRC) {
        struct data my_data = {0};
        set_data_struct(&my_data, 2, 0, OP, &s21_do_mult);
        status = push_manager(my_data, numbers, operators);
    }
    *operators = s21_push(data, *operators);
    return status;
}

int action_close_bracket(unit **numbers, unit **operators) {
    int status = SUCCESS;
    while (*operators && (*operators)->data.type != BRO && status == SUCCESS) {
        status = (*operators)->data.action(numbers, operators);
    }
    if (*operators == NULL)
        status = NOT_FOUND_OPEN_BRACKET;
    else if (status == SUCCESS) {
        *operators = s21_pop(*operators);
    }
    return status;
}

int push_func(struct data data, unit **numbers, unit **operators,
              int last_type) {
    int status = SUCCESS;
    if (last_type == NUM || last_type == VAR || last_type == BRC) {
        struct data my_data = {0};
        set_data_struct(&my_data, 2, 0, OP, &s21_do_mult);
        status = push_manager(my_data, numbers, operators);
    }
    *operators = s21_push(data, *operators);
    return status;
}

// return 0 - if unstack not necessery! overwise 1 means we have to unstack
// current options
int check_possible_push(struct data data, unit **operators) {
    int status = SUCCESS;
    if (*operators && (*operators)->data.priority > data.priority) {
        status = NEED_UNSTACK;
    }
    return status;
}

int push_operator(struct data *data, unit **numbers, unit **operators,
                  int last_type) {
    int status = SUCCESS;
    if ((data->symbol == '+') && (last_type == -1 || last_type == BRO ||
                                  last_type == UOP || last_type == BOP)) {
        data->type = UOP;
        data->action = &unar_plus;
        data->priority = 5;
    } else if (data->symbol == '-') {
        if (!(last_type == -1 || last_type == BRO || last_type == UOP ||
              last_type == BOP)) {
            struct data my_data = {0};
            my_data.symbol = '+';
            set_data_struct(&my_data, 1, 0, OP, &s21_do_plus);
            status = push_manager(my_data, numbers, operators);
        }
        data->type = UOP;
        data->action = &unar_minus;
        data->priority = 5;
    } else {
        data->type = BOP;
    }
    status = check_possible_push(*data, operators);
    if (status == NEED_UNSTACK) status = unstack(*data, numbers, operators);
    if (status == SUCCESS) {
        *operators = s21_push(*data, *operators);
    }
    return status;
}

int push_variable(struct data data, unit **numbers, unit **operators,
                  int last_type) {
    int status = SUCCESS;
    if (last_type == VAR) {
        status = FORGOT_OPERATOR;
    } else if (last_type == BRC) {
        status = MISSING_OPERATOR;
    } else if (last_type == NUM) {
        struct data my_data = {0};
        set_data_struct(&my_data, 2, 0, OP, &s21_do_mult);
        status = push_manager(my_data, numbers, operators);
        *numbers = s21_push(data, *numbers);
    } else {
        *numbers = s21_push(data, *numbers);
    }
    return status;
}

// int push_unar_operator(struct data data, unit **numbers, unit **operators) {
//     int status = SUCCESS;
//     status = data.action(numbers, operators);
//     return status;
// }

// int push_binar_operator(struct data data, unit **numbers, unit **operators) {
//     int status = SUCCESS;
//     status = data.action(numbers, operators);
//     return status;
// }

static int last_type;

void reset_last_type() { last_type = -1; }

int push_manager(struct data data, unit **numbers, unit **operators) {
    int status = SUCCESS;
    // last_type = -1;
    if (data.type == NUM)
        status = push_number(data, numbers, last_type);
    else if (data.type == BRO)
        status = push_open_bracket(data, numbers, operators, last_type);
    else if (data.type == BRC) {
        status = action_close_bracket(numbers, operators);
    } else if (data.type == FUNC) {
        status = push_func(data, numbers, operators, last_type);
    } else if (data.type == OP) {
        status = push_operator(&data, numbers, operators, last_type);
    } else if (data.type == VAR) {
        status = push_variable(data, numbers, operators, last_type);
    }
    last_type = data.type;
    return status;
}
