#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct s21_literal s21_literal;

struct data {
    int id;
    int priority;
    double value;
    int count_operands;
    void (*action)(s21_literal **, s21_literal **);
};

struct s21_literal {
    struct data data;
    struct s21_literal *next;
};

char *parse_num(char *symbol, int *status, s21_literal **root_numbers);

char *parse_string(char *symbol, int *status, s21_literal **root_operators);

char *parse_operator(char *symbol, int *status, s21_literal *root_numbers,
                     s21_literal *root_operators);

void parse(char *str, s21_literal **root_numbers, s21_literal **root_operators);

/*******************************/
/*                             */
/*            stack            */
/*                             */
/*******************************/

/**
 * @brief Function for new element into list
 *
 * @param data structure with data (value, priority, callback func and so on)
 * @param root pointer to current root element of list. Add new element after
 * here
 *
 * @return pointer to new list (new last elemet inside it)
 */
s21_literal *s21_push(struct data data, s21_literal *root);

/**
 * Function for remove last element feom list and freeing memory.
 *
 * @param root pointer to last element of list
 * @return pointer to new list (new last elemet inside it)
 */
s21_literal *s21_pop(s21_literal *root);

/*******************************/
/*                             */
/*            help             */
/*                             */
/*******************************/

void print_stack(s21_literal *root);
char *to_lower(char *target);

/*******************************/
/*                             */
/*           action            */
/*                             */
/*******************************/

void do_nothing(s21_literal *first, s21_literal *second);
void s21_do_cos(s21_literal **numbers, s21_literal **operators);