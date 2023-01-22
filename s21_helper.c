#include "s21_polish.h"

void print_stack(unit *root) {
    unit *copy = root;
    if (copy == NULL) {
        printf("NO ELEMENT HERE\n");
    } else {
        while (copy != NULL) {
            printf("------------------\n");
            printf("|                |\n");
            printf("| val = %.6lf |\n", copy->data.value);
            printf("| type = %8d |\n", copy->data.type);
            printf("|                |\n");
            printf("------------------\n");
            copy = copy->next;
            printf("         |        \n");
            printf("         V        \n");
        }
        printf("        END       \n");
    }
}

char *to_lower(char *target) {
    int len = strlen(target);
    char *str = (char *)calloc(len + 1, sizeof(char));
    for (int i = 0; i < len; i++) {
        if (target[i] >= 'A' && target[i] <= 'Z') {
            str[i] = target[i] + 32;
        } else {
            str[i] = target[i];
        }
    }
    str[len] = '\0';
    return str;
}

int check_2_values(unit *numbers) {
    int status = SUCCESS;
    if (numbers && ((numbers->data.type != NUM) ||
                    (numbers->next && numbers->next->data.type != NUM))) {
        status = HAVE_VAR;
    } else if (!numbers || !numbers->next)
        status = NOT_ENOUGHT_NUMBERS;
    return status;
}

int check_1_values(unit *numbers) {
    int status = SUCCESS;
    if (numbers && numbers->data.type != NUM)
        status = HAVE_VAR;
    else if (!numbers)
        status = NOT_ENOUGHT_NUMBERS;
    return status;
}

void transform_list_unar(struct data data, unit **numbers, unit **operators) {
    *numbers = s21_pop(*numbers);
    *operators = s21_pop(*operators);
    *numbers = s21_push(data, *numbers);
}

void transform_list_binar(struct data data, unit **numbers, unit **operators) {
    for (int i = 0; i < 2; i++) {
        *numbers = s21_pop(*numbers);
    }
    *operators = s21_pop(*operators);
    *numbers = s21_push(data, *numbers);
}

void set_data_struct(struct data *data, int priority, double value, int type,
                     int (*action)(unit **, unit **)) {
    data->priority = priority;
    data->value = value;
    data->type = type;
    data->action = action;
}

int unstack(struct data data, unit **numbers, unit **operators) {
    int status = SUCCESS;
    while (*operators && (*operators)->data.priority > data.priority &&
           status == 0) {
        status = (*operators)->data.action(numbers, operators);
    }
    return status;
}

void print_problem(int status) {
    if (status == 2)
        printf("Проблема в парсинге чисел");
    else if (status == 3)
        printf("Проставлен дополнительный лишний символ . или е");
    else if (status == 4)
        printf("Пропущен оператор");
    else if (status == 5)
        printf("Пропущен оператор");
    else if (status == 6)
        printf("Неверная позиция числа и переменной");
    else if (status == 7)
        printf("Не найдена открывающая скобка");
    else if (status == 8)
        printf("Не хватает числе для отработки функции");
    else if (status == 9)
        printf("Что-то пошло не так");
}