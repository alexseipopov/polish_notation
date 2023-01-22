#include "s21_polish.h"

int if_in(char target, char *arr) {
    int status = 0;
    if (target != '\0' && strchr(arr, target) != NULL) {
        status = 1;
    }
    return status;
}

char *parse_hex(char *symbol, int *status, char *output_str, int *have_digit) {
    if (*status == LOCAL_STATUS_OFF && strstr(symbol, "0x") == symbol) {
        int iterator = 2;
        *status = LOCAL_STATUS_ON;
        for (int i = 0; i < 2; i++) {
            output_str[i] = *(symbol++);
        }
        while (if_in(*symbol, HEX_SYMBOLS) && *symbol != '\0') {
            output_str[iterator] = *symbol;
            symbol = symbol + 1;
            iterator++;
        }
        if (iterator > 2) {
            *have_digit = 1;
        }
    }
    return symbol;
}

char *parce_dec(char *symbol, int *status, char *output_str, int *have_digit) {
    if (if_in(*symbol, ALLOW_DIGIT_SYMBOL) && *status == LOCAL_STATUS_OFF) {
        int iterator = 0;
        int point = 1;
        int e = 1;
        while ((*symbol >= '0' && *symbol <= '9') ||
               (*symbol == '.' && point && e) ||
               (*symbol == 'e' && e && *have_digit) ||
               (*symbol == '-' && *(symbol - 1) == 'e')) {
            if (*symbol >= '0' && *symbol <= '9') *have_digit = 1;
            if (point && *symbol == '.' && e) point = 0;
            if (e && *symbol == 'e') e = 0;
            output_str[iterator] = *symbol;
            symbol = symbol + 1;
            *status = LOCAL_STATUS_ON;
            iterator++;
        }
    }
    return symbol;
}

char *parse_num(char *symbol, int *status, unit **result,
                unit **stack_operator) {
    char *str = (char *)calloc(strlen(symbol), sizeof(char));
    int have_digit = 0;
    int local_status = LOCAL_STATUS_OFF;
    symbol = parse_hex(symbol, &local_status, str, &have_digit);
    symbol = parce_dec(symbol, &local_status, str, &have_digit);
    if (*status != SUCCESS) {
        if (local_status == LOCAL_STATUS_ON && have_digit) {
            struct data data = {0};
            set_data_struct(&data, 0, atof(str), NUM, NULL);
            *status = push_manager(data, result, stack_operator);
        } else if (!have_digit && local_status) {
            *status = PARSING_NUMBER_ERROR;
        }
    }
    free(str);
    return symbol;
}

char *parse_string(char *symbol, int *status, unit **result,
                   unit **stack_operator) {
    char *symbolic[9] = {"cos",  "sin",  "tan", "acos", "asin",
                         "atan", "sqrt", "ln",  "log"};
    int (*func[9])(unit **, unit **) = {
        &s21_do_cos,  &s21_do_sin,  &s21_do_tan, &s21_do_acos, &s21_do_asin,
        &s21_do_atan, &s21_do_sqrt, &s21_do_ln,  &s21_do_log};
    for (int i = 0; i < 9 && *status == SUCCESS; i++) {
        if (strstr(symbol, symbolic[i]) == symbol) {
            struct data data = {0};
            set_data_struct(&data, 4, 0, FUNC, func[i]);
            *status = push_manager(data, result, stack_operator);
            symbol = symbol + strlen(symbolic[i]);
            break;
        }
    }
    return symbol;
}

char *parse_operator(char *symbol, int *status, unit **result,
                     unit **stack_operator) {
    char *operator[6] = {"+", "-", "/", "*", "mod", "^"};
    int (*func[6])(unit **, unit **) = {&s21_do_plus, &s21_do_minus,
                                        &s21_do_div,  &s21_do_mult,
                                        &s21_do_mod,  &s21_do_pow};
    for (int i = 0; i < 6 && *status == SUCCESS; i++) {
        if (strstr(symbol, operator[i]) == symbol) {
            struct data data = {0};
            data.symbol = (*symbol == '+' || *symbol == '-') ? *symbol : '\0';
            set_data_struct(&data, (i + 4) / 3, 0, OP, func[i]);
            *status = push_manager(data, result, stack_operator);
            symbol = symbol + strlen(operator[i]);
            break;
        }
    }
    return symbol;
}

char *parse_variable(char *symbol, int *status, unit **result,
                     unit **stack_operator) {
    if (strstr(symbol, "x") == symbol && *status == SUCCESS) {
        struct data data = {0};
        set_data_struct(&data, 0, 0, VAR, NULL);
        *status = push_manager(data, result, stack_operator);
        symbol++;
    }
    return symbol;
}

char *parse_bracket(char *symbol, int *status, unit **result,
                    unit **stack_operator) {
    char brs[2] = {'(', ')'};
    int brs_type[2] = {BRO, BRC};
    // int (*func[2])(unit **, unit **) = {&open_bracket, &close_bracket};
    for (int i = 0; i < 2 && *status == SUCCESS; i++) {
        if (strchr(symbol, brs[i]) == symbol) {
            struct data data = {0};
            set_data_struct(&data, 0, 0, brs_type[i], NULL);
            *status = push_manager(data, result, stack_operator);
            symbol++;
            break;
        }
    }
    return symbol;
}

void parce_illigal(char *symbol, int *status) {
    if (if_in(*symbol, ILLIGAL_LIST)) *status = EXTRA_ILLIGAL_SYMBOL;
}

int resolve_lists(unit **result, unit **stack_operator) {
    int status = SUCCESS;
    while (*stack_operator && status == SUCCESS) {
        if ((*stack_operator)->data.action == NULL) {
            status = SOMETHING_WRONG;
            break;
        }
        status = (*stack_operator)->data.action(result, stack_operator);
    }
    return status;
}

int parse(char *str, unit **result, unit **stack_operator) {
    int status = SUCCESS;
    reset_last_type();
    while (*str != '\0' && status == SUCCESS) {
        status = PARSING_ERROR;
        str = parse_string(str, &status, result, stack_operator);
        str = parse_operator(str, &status, result, stack_operator);
        str = parse_variable(str, &status, result, stack_operator);
        str = parse_bracket(str, &status, result, stack_operator);
        str = parse_num(str, &status, result, stack_operator);
        parce_illigal(str, &status);
        if (*str == ' ') {
            str++;
            status = SUCCESS;
        }
        if (status == PARSING_ERROR) printf("Error parsing\n");
        if (status >= PARSING_NUMBER_ERROR) printf("Error calculation\n");
    }
    if (status == SUCCESS) {
        status = resolve_lists(result, stack_operator);
    }
    return status;
}

int s21_solve_result(char *target, double variable, double *res) {
    unit *result = NULL;
    unit *root_operands = NULL;
    target = to_lower(target);
    int status = parse(target, &result, &root_operands);
    if (status == SUCCESS) {
        status = resolve_struct(&result, variable, res);
    }
    return status;
}