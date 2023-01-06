#include "s21_polish.h"

char *parse_num(char *symbol, int *status, s21_literal *root_numbers,
                s21_literal *root_operators) {
    char *str = (char *)calloc(255, sizeof(char));
    int iterator = 0;
    int point = 1;
    int e = 1;
    while ((*symbol >= '0' && *symbol <= '9') || (*symbol == '.' && point) ||
           ((*symbol == 'e' || *symbol == 'E') && e)) {
        if (point && *symbol == '.') point = 0;
        if (e && (*symbol == 'e' || *symbol == 'E')) e = 0;  // TODO пропарсить минус после e
        printf("%c number\n", *symbol);
        str[iterator] = *symbol;
        symbol = symbol + 1;
        *status = 1;
        iterator++;
    }
    if (*status == 1) {
        struct data data;
        data.value = atof(str);
        s21_literal *current = s21_init(data);
        root_numbers = s21_push(current, root_numbers);
        printf("%lf <----\n", atof(str));
        s21_literal *cp = root_numbers;
        while (cp != NULL) {
            printf("%llf :-> ", cp->data.value);
            cp = cp->next;
        }
    }
    return symbol;
}

char *parse_string(char *symbol, int *status, s21_literal *root_numbers,
                   s21_literal *root_operators) {
    char *symbolic[10] = {"cos",  "sin",  "tan", "acos", "asin",
                          "atan", "sqrt", "ln",  "log",  "mod"};
    int len = 0;
    for (int i = 0; i < 10; i++) {
        if (strstr(symbol, symbolic[i]) == symbol) {
            len = strlen(symbolic[i]);
            for (int k = 0; k < len; k++) {
                printf("%c", symbol[k]);
            }
            printf(" <------\n");
            *status = 1;
            symbol = symbol + len;
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

void parse(char *str, s21_literal *root_numbers, s21_literal *root_operators) {
    int status;
    while (*str != '\0') {
        status = 0;
        str = parse_num(str, &status, root_numbers, root_operators);
        str = parse_string(str, &status, root_numbers, root_operators);
        str = parse_operator(str, &status, root_numbers, root_operators);
        if (*str == ' ') str++;
        if (status == 0) {
            printf("%s\n", str);
            printf("^\n");
            printf("| error here \n");
            break;
        }
    }
}