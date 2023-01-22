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

// servise statuses
#define NEED_UNSTACK 1

// statuses
#define SUCCESS 0
#define PARSING_ERROR 1
#define FAILURE 1
#define PARSING_NUMBER_ERROR 2
#define EXTRA_ILLIGAL_SYMBOL 3
#define FORGOT_OPERATOR 4
#define MISSING_OPERATOR 5
#define CHANGE_VAR_POSITION 6
#define NOT_FOUND_OPEN_BRACKET 7
#define NOT_ENOUGHT_NUMBERS 8
#define SOMETHING_WRONG 9
#define HAVE_VAR 10  // продумать его в другое место

typedef struct unit unit;

struct data {
    // TODO удалить id он вроде не нужен после статика а менеджере
    int id;
    int priority;
    double value;
    int type;
    char symbol;
    int (*action)(unit **, unit **);
};

struct unit {
    struct data data;
    struct unit *next;
};

enum types { BRO, BRC, FUNC, NUM, OP, UOP, BOP, VAR };

char *parse_num(char *symbol, int *status, unit **result,
                unit **stack_operator);

char *parse_string(char *symbol, int *status, unit **result,
                   unit **stack_operator);

char *parse_operator(char *symbol, int *status, unit **result,
                     unit **stack_operator);

/**
 * @brief Entry function for making linked-list
 * In simple case (withoutt variable[-s]) return only onse number in
 * linked-list, available on `result` pointer In case with variables - function
 * return linked list of simplified input data for next using in calculate the
 * answer or plotting
 *
 * @param str pointer to origin input string
 * @param result poinrer on pointer to root of linked-list. Will contains
 * `answer` of this function
 * @param
 */
int parse(char *str, unit **result, unit **stack_operator);

char *parse_bracket(char *symbol, int *status, unit **result,
                    unit **stack_operator);

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
unit *s21_push(struct data data, unit *root);

/**
 * Function for remove last element feom list and freeing memory.
 *
 * @param root pointer to last element of list
 * @return pointer to new list (new last elemet inside it)
 */
unit *s21_pop(unit *root);

/*******************************/
/*                             */
/*            help             */
/*                             */
/*******************************/

void print_stack(unit *root);
char *to_lower(char *target);

/**
 * @brief Check list of numbers to be exist anought value(s)
 *
 * @param numbers pointer to list for check
 * @return status: 0 - ok, 1 - failure
 */
int check_2_values(unit *numbers);
int check_1_values(unit *numbers);

void transform_list_unar(struct data data, unit **numbers, unit **operators);
void transform_list_binar(struct data data, unit **numbers, unit **operators);
void set_data_struct(struct data *data, int priority, double value, int type,
                     int (*action)(unit **, unit **));

int unstack(struct data data, unit **numbers, unit **operators);
void print_problem(int status);

/*******************************/
/*                             */
/*           action            */
/*                             */
/*******************************/

int unar_action(unit **numbers, unit **operators, double (*action)(double));
int binar_action(unit **numbers, unit **operators,
                 double (*action)(double, double));

int unar_minus(unit **numbers, unit **operators);
int unar_plus(unit **numbers, unit **operators);
int s21_do_cos(unit **numbers, unit **operators);
int s21_do_sin(unit **numbers, unit **operators);
int s21_do_tan(unit **numbers, unit **operators);
int s21_do_acos(unit **numbers, unit **operators);
int s21_do_asin(unit **numbers, unit **operators);
int s21_do_atan(unit **numbers, unit **operators);
int s21_do_sqrt(unit **numbers, unit **operators);
int s21_do_ln(unit **numbers, unit **operators);
int s21_do_log(unit **numbers, unit **operators);

double my_plus(double first, double second);
double my_minus(double first, double second);
double my_mult(double first, double second);
double my_div(double first, double second);
int s21_do_plus(unit **numbers, unit **operators);
int s21_do_minus(unit **numbers, unit **operators);
int s21_do_div(unit **numbers, unit **operators);
int s21_do_mult(unit **numbers, unit **operators);
int s21_do_mod(unit **numbers, unit **operators);
int s21_do_pow(unit **numbers, unit **operators);

/*******************************/
/*                             */
/*          managers           */
/*                             */
/*******************************/

int push_manager(struct data data, unit **numbers, unit **operators);
int push_number(struct data data, unit **numbers, int last_type);
int push_open_bracket(struct data data, unit **numbers, unit **operators,
                      int last_type);
int action_close_bracket(unit **numbers, unit **operators);
int push_func(struct data data, unit **numbers, unit **operators,
              int last_type);
int push_operator(struct data *data, unit **numbers, unit **operators,
                  int last_type);
int push_variable(struct data data, unit **numbers, unit **operators,
                  int last_type);
int push_manager(struct data data, unit **numbers, unit **operators);

int resolve_struct(unit **numbers, double variable, double *res);
int check_possible_push(struct data data, unit **operators);
int resolve_lists(unit **result, unit **stack_operator);
int s21_solve_result(char *target, double variable, double *res);
void reset_last_type();