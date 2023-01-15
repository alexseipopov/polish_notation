#include "s21_polish.h"

void print_stack(s21_literal *root) {
    s21_literal *copy = root;
    if (copy == NULL) {
        printf("NO ELEMENT HERE\n");
    } else {
        while (copy != NULL) {
            printf("------------------\n");
            printf("|                |\n");
            printf("| val = %.6lf |\n", copy->data.value);
            printf("| val = %8d |\n", copy->data.id);
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

int check_2_values(s21_literal *numbers) {
    int status = (numbers && numbers->next) ? SUCCESS : FAILURE;
    return status;
}

int check_1_values(s21_literal *numbers) {
    int status = (numbers) ? SUCCESS : FAILURE;
    return status;
}

void transform_list_unar(struct data data, s21_literal **numbers,
                         s21_literal **operators) {
    *numbers = s21_pop(*numbers);
    *operators = s21_pop(*operators);
    *numbers = s21_push(data, *numbers);
}

void transform_list_binar(struct data data, s21_literal **numbers,
                          s21_literal **operators) {
    for (int i = 0; i < 2; i++) {
        *numbers = s21_pop(*numbers);
    }
    *operators = s21_pop(*operators);
    *numbers = s21_push(data, *numbers);
}