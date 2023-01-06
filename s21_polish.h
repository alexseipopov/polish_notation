#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct data {
    int id;
    int priority;
    long double value;
};

typedef struct s21_literal {
    struct data data;
    struct s21_literal *next;
} s21_literal;

s21_literal *s21_init(struct data data);
s21_literal *s21_push(s21_literal *target, s21_literal *root);
s21_literal *s21_pop(s21_literal *root);

int parse_num(char *symbol);

int parse_string(char *symbol);

int parse_operator(char *symbol);

void parse(char *str);