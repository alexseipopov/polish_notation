#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
    int id;
    int priority;
    long double value;
    int count_operands;
};

typedef struct s21_literal {
    struct data data;
    struct s21_literal *next;
} s21_literal;

s21_literal *s21_init(struct data data);
s21_literal *s21_push(s21_literal *target, s21_literal *root);
s21_literal *s21_pop(s21_literal *root);

char *parse_num(char *symbol, int *status, s21_literal *root_numbers,
                s21_literal *root_operators);

char *parse_string(char *symbol, int *status, s21_literal *root_numbers,
                   s21_literal *root_operators);

char *parse_operator(char *symbol, int *status, s21_literal *root_numbers,
                     s21_literal *root_operators);

void parse(char *str, s21_literal *root_numbers, s21_literal *root_operators);