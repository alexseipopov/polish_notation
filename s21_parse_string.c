#include "s21_polish.h"

char *parse_num(char *symbol, int *status, s21_literal **root_numbers) {
    char *str = (char *)calloc(strlen(symbol), sizeof(char));
    int iterator = 0;
    int point = 1;
    int e = 1;

    while ((*symbol >= '0' && *symbol <= '9') || (*symbol == '.' && point) ||
           (*symbol == 'e' && e) || (*symbol == '-' && *(symbol - 1) == 'e')) {
        if (point && *symbol == '.') point = 0;
        if (e && *symbol == 'e') e = 0;
        str[iterator] = *symbol;
        symbol = symbol + 1;
        *status = SUCCESS;
        iterator++;
    }
    if (*status == SUCCESS) {
        struct data data = {0};
        data.value = atof(str);
        *root_numbers = s21_push(data, *root_numbers);
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
            data.action = func[i];
            data.priority = 4;
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
    struct data data = {0};
    int (*func[6])(s21_literal **, s21_literal **) = {
        &s21_do_plus, &s21_do_minus, &s21_do_div,
        &s21_do_mult, &s21_do_mod,   &s21_do_pow};
    for (int i = 0; i < 6; i++) {
        if (strstr(symbol, operator[i]) == symbol) {
            data.action = func[i];
            data.priority = (i + 4) / 3;
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
        data.value = var;
        *root_numbers = s21_push(data, *root_numbers);
        *status = SUCCESS;
        symbol++;
    }
    return symbol;
}

char *parse_bracket(char *symbol, int *status, s21_literal **root_numbers,
                    s21_literal **root_operators) {
    char brs[2] = {'(', ')'};
    int (*func[2])(s21_literal **, s21_literal **) = {&open_bracket,
                                                      &close_bracket};
    for (int i = 0; i < 2; i++) {
        if (strchr(symbol, brs[i]) == symbol) {
            struct data data = {0};
            data.action = func[i];
            data.priority = 0;
            *status = push_operator_manager(data, root_numbers, root_operators);
            symbol++;
            break;
        }
    }
    return symbol;
}

void parse(char *str, s21_literal **root_numbers, s21_literal **root_operators,
           double var) {
    int status = SUCCESS;
    while (*str != '\0' && status == SUCCESS) {
        status = PARSING_ERROR;
        str = parse_num(str, &status, root_numbers);
        str = parse_string(str, &status, root_numbers, root_operators);
        str = parse_operator(str, &status, root_numbers, root_operators);
        str = parse_variable(str, &status, root_numbers, var);
        str = parse_bracket(str, &status, root_numbers, root_operators);
        if (*str == ' ') {
            str++;
            status = SUCCESS;
        }
        if (status == PARSING_ERROR) printf("Error parsing\n");
        if (status >= MATH_ERROR) printf("Error calculation\n");
    }
}