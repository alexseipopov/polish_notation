#include "s21_polish.h"

char *parse_num(char *symbol, int *status, s21_literal **root_numbers) {
    char *str = (char *)calloc(255, sizeof(char));
    int iterator = 0;
    int point = 1;
    int e = 1;
    struct data data = {0};
    s21_literal *current = NULL;
    while ((*symbol >= '0' && *symbol <= '9') || (*symbol == '.' && point) ||
           (*symbol == 'e' && e) || (*symbol == '-' && *(symbol - 1) == 'e')) {
        if (point && *symbol == '.') point = 0;
        if (e && *symbol == 'e') e = 0;
        str[iterator] = *symbol;
        symbol = symbol + 1;
        *status = 1;
        iterator++;
    }
    if (*status == 1) {
        data.value = atof(str);
        *root_numbers = s21_push(data, *root_numbers);
    }
    free(str);
    return symbol;
}

char *parse_string(char *symbol, int *status, s21_literal **root_operators) {
    char *symbolic[9] = {"cos",  "sin",  "tan", "acos", "asin",
                         "atan", "sqrt", "ln",  "log"};
    void (*func[1])(s21_literal **, s21_literal **) = {&s21_do_cos};
    int len = 0;
    struct data data;
    for (int i = 0; i < 9; i++) {
        if (strstr(symbol, symbolic[i]) == symbol) {
            len = strlen(symbolic[i]);
            data.action = func[i];
            data.priority = 4;
            s21_push(data, &root_operators);
            *status = 1;
            symbol = symbol + len;
            break;
        }
    }

    return symbol;
}

char *parse_operator(char *symbol, int *status, s21_literal *root_numbers,
                     s21_literal *root_operators) {
    char operator[7] = {'+', '-', '/', '*', '(', ')', '^'};
    for (int i = 0; i < 7; i++) {
        if (strchr(symbol, operator[i]) == symbol) {
            printf("%c operator\n", *symbol);
            *status = 1;
            symbol = symbol + 1;
        }
    }

    return symbol;
}

void parse(char *str, s21_literal **root_numbers, s21_literal **root_operators) {
    int status;
    while (*str != '\0') {
        status = 0;
        str = parse_num(str, &status, root_numbers);
        str = parse_string(str, &status, root_operators);
        str = parse_operator(str, &status, *root_numbers, root_operators);
        // str = parse_variable(str);
        if (*str == ' ') {
            str++;
            status = 1;
        }
        if (status == 0) {
            printf("%s\n", str);
            printf("^\n");
            printf("| error here \n");
            break;
        }
    }
}