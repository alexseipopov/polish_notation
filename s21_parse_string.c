#include "s21_polish.h"

int if_in(char target, char *arr) {
    int status = 0;
    if (target != '\0' && strchr(arr, target) != NULL) {
        status = 1;
    }
    return status;
}

char *parse_hex(char *symbol, int *status, char *output_str, int *have_digit) {
    if (strstr(symbol, "0x") == symbol && *status == LOCAL_STATUS_OFF) {
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

char *parse_num(char *symbol, int *status, s21_literal **root_numbers) {
    char *str = (char *)calloc(strlen(symbol), sizeof(char));
    int have_digit = 0;
    int local_status = LOCAL_STATUS_OFF;
    symbol = parse_hex(symbol, &local_status, str, &have_digit);
    symbol = parce_dec(symbol, &local_status, str, &have_digit);
    if (local_status == LOCAL_STATUS_ON && have_digit) {
        struct data data = {0};
        data.value = atof(str);
        *root_numbers = s21_push(data, *root_numbers);
        *status = SUCCESS;
    } else if (!have_digit) {
        *status = PARSING_NUMBER_ERROR;
    }
    free(str);
    return symbol;
}

char *parse_string(char *symbol, int *status, s21_literal **root_numbers,
                   s21_literal **root_operators) {
    char *symbolic[9] = {"cos",  "sin",  "tan", "acos", "asin",
                         "atan", "sqrt", "ln",  "log"};
    int (*func[9])(s21_literal **, s21_literal **) = {
        &s21_do_cos,  &s21_do_sin,  &s21_do_tan, &s21_do_acos, &s21_do_asin,
        &s21_do_atan, &s21_do_sqrt, &s21_do_ln,  &s21_do_log};
    for (int i = 0; i < 9; i++) {
        if (strstr(symbol, symbolic[i]) == symbol) {
            struct data data = {0};
            set_data_struct(&data, 4, 0, FUNC, func[i]);
            *status = push_operator_manager(data, root_numbers, root_operators);
            symbol = symbol + strlen(symbolic[i]);
            break;
        }
    }
    return symbol;
}

char *parse_operator(char *symbol, int *status, s21_literal **root_numbers,
                     s21_literal **root_operators) {
    char *operator[6] = {"+", "-", "/", "*", "mod", "^"};
    int (*func[6])(s21_literal **, s21_literal **) = {
        &s21_do_plus, &s21_do_minus, &s21_do_div,
        &s21_do_mult, &s21_do_mod,   &s21_do_pow};
    for (int i = 0; i < 6; i++) {
        if (strstr(symbol, operator[i]) == symbol) {
            struct data data = {0};
            set_data_struct(&data, (i + 4) / 3, 0, OP, func[i]);
            *status = push_operator_manager(data, root_numbers, root_operators);
            symbol = symbol + strlen(operator[i]);
        }
    }
    return symbol;
}

char *parse_variable(char *symbol, int *status, s21_literal **root_numbers,
                     double var) {
    if (strstr(symbol, "x") == symbol) {
        struct data data = {0};
        set_data_struct(&data, 0, var, VAR, NULL);
        *root_numbers = s21_push(data, *root_numbers);
        *status = SUCCESS;
        symbol++;
    }
    return symbol;
}

char *parse_bracket(char *symbol, int *status, s21_literal **root_numbers,
                    s21_literal **root_operators) {
    char brs[2] = {'(', ')'};
    int brs_type[2] = {BRO, BRC};
    int (*func[2])(s21_literal **, s21_literal **) = {&open_bracket,
                                                      &close_bracket};
    for (int i = 0; i < 2; i++) {
        if (strchr(symbol, brs[i]) == symbol) {
            struct data data = {0};
            set_data_struct(&data, 0, 0, brs_type[i], func[i]);
            *status = push_operator_manager(data, root_numbers, root_operators);
            symbol++;
            break;
        }
    }
    return symbol;
}

void parce_illigal(char *symbol, int *status) {
    if (if_in(*symbol, ILLIGAL_LIST)) *status = EXTRA_ILLIGAL_SYMBOL;
}

void parse(char *str, s21_literal **root_numbers, s21_literal **root_operators,
           double var) {
    int status = SUCCESS;
    while (*str != '\0' && status == SUCCESS) {
        status = PARSING_ERROR;
        // TODO переместить parse_num в последний парсинг, это избавит от
        // необходимости в каждом остальном парсинге проверять не было ли там
        // ошибки вычисления
        str = parse_string(str, &status, root_numbers, root_operators);
        str = parse_operator(str, &status, root_numbers, root_operators);
        str = parse_variable(str, &status, root_numbers, var);
        str = parse_bracket(str, &status, root_numbers, root_operators);
        str = parse_num(str, &status, root_numbers);
        parce_illigal(str, &status);
        if (*str == ' ') {
            str++;
            status = SUCCESS;
        }
        if (status == PARSING_ERROR) printf("Error parsing\n");
        if (status >= PARSING_NUMBER_ERROR) printf("Error calculation\n");
    }
}