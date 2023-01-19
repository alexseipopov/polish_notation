#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEX_SYMBOLS "0123456789abcdef"
#define ALLOW_DIGIT_SYMBOL "0123456789.e"
#define ILLIGAL_LIST ".e"

// local statuses
#define LOCAL_STATUS_OFF 0
#define LOCAL_STATUS_ON 1

// statuses
#define SUCCESS 0
#define PARSING_ERROR 1
#define FAILURE 1
#define PARSING_NUMBER_ERROR 2
#define EXTRA_ILLIGAL_SYMBOL 3
#define MATH_ERROR 4

typedef struct s21_literal s21_literal;

struct data {
    int id;
    int priority;
    double value;
    int type;
    int (*action)(s21_literal **, s21_literal **);
};

struct s21_literal {
    struct data data;
    struct s21_literal *next;
};

enum types { BRO, BRC, FUNC, NUM, OP, UOP, BOP, VAR };

char *parse_num(char *symbol, int *status, s21_literal **root_numbers);

char *parse_string(char *symbol, int *status, s21_literal **root_numbers,
                   s21_literal **root_operators);

char *parse_operator(char *symbol, int *status, s21_literal **root_numbers,
                     s21_literal **root_operators);

void parse(char *str, s21_literal **root_numbers, s21_literal **root_operators,
           double var);

char *parse_bracket(char *symbol, int *status, s21_literal **root_numbers,
                    s21_literal **root_operators);

/*******************************/
/*                             */
/*            stack            */
/*                             */
/*******************************/

/**
 * @brief Function for new element into list. If first element does not exist -
 * function create one.
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

/**
 * @brief Check list of numbers to be exist anought value(s)
 *
 * @param numbers pointer to list for check
 * @return status: 0 - ok, 1 - failure
 */
int check_2_values(s21_literal *numbers);
int check_1_values(s21_literal *numbers);

void transform_list_unar(struct data data, s21_literal **numbers,
                         s21_literal **operators);
void transform_list_binar(struct data data, s21_literal **numbers,
                          s21_literal **operators);
void set_data_struct(struct data *data, int priority, double value, int type,
                     int (*action)(s21_literal **, s21_literal **));

/*******************************/
/*                             */
/*           action            */
/*                             */
/*******************************/

int s21_do_cos(s21_literal **numbers, s21_literal **operators);
int s21_do_sin(s21_literal **numbers, s21_literal **operators);
int s21_do_tan(s21_literal **numbers, s21_literal **operators);
int s21_do_acos(s21_literal **numbers, s21_literal **operators);
int s21_do_asin(s21_literal **numbers, s21_literal **operators);
int s21_do_atan(s21_literal **numbers, s21_literal **operators);
int s21_do_sqrt(s21_literal **numbers, s21_literal **operators);
int s21_do_ln(s21_literal **numbers, s21_literal **operators);
int s21_do_log(s21_literal **numbers, s21_literal **operators);

int s21_do_plus(s21_literal **numbers, s21_literal **operators);
int s21_do_minus(s21_literal **numbers, s21_literal **operators);
int s21_do_div(s21_literal **numbers, s21_literal **operators);
int s21_do_mult(s21_literal **numbers, s21_literal **operators);
int s21_do_mod(s21_literal **numbers, s21_literal **operators);
int s21_do_pow(s21_literal **numbers, s21_literal **operators);
int open_bracket(s21_literal **numbers, s21_literal **operators);
int close_bracket(s21_literal **numbers, s21_literal **operators);

/*******************************/
/*                             */
/*          managers           */
/*                             */
/*******************************/

int push_operator_manager(struct data data, s21_literal **numbers,
                          s21_literal **operators);
int counter(s21_literal **numbers, s21_literal **operators);