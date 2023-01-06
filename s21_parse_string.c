#include "s21_polish.h"

int parse_num(char *symbol) {
    int status = 0;
    if (*symbol >= '0' && *symbol <= '9') {
        printf("%c number\n", *symbol);
        status = 1;
        symbol = symbol + 1;
    }
    return status;
}

int parse_string(char *symbol) {
    int status = 0;
    if (*symbol >= 'a' && *symbol <= 'z') {
        printf("%c symbol\n", *symbol);
        status = 1;
       symbol = symbol + 1;
    }
    return status;
}

int parse_operator(char *symbol) {
    int status = 0;
    if (*symbol == '+' || *symbol == '-') {
        printf("%c operator\n", *symbol);
        status = 1;
        symbol = symbol + 1;
    }
    return status;
}

void parse(char *str) {
    int number = 0;
    int string = 0;
    int operator = 0;
    while (*str != '\0') {
        number = parse_num(str);
        if (!number) {
            string = parse_string(str);
            if (!string) {
                operator = parse_operator(str);
                if (!operator && *str != ' ') {
                    break;
                }
            }
        }
        if (*str == ' ') str++;
    }
}