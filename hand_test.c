#include "s21_polish.h"

s21_literal *s21_init(struct data data) {
    s21_literal *target = (s21_literal *)calloc(1, sizeof(s21_literal));
    target->next = NULL;
    target->data = data;
    printf("put val %llf\n", target->data.value);
    return target;
}

int main(void) {
    // char *str = "123    ";
    // int k = atoi(str);
    // printf("%d\n", k);
    // struct data d;
    // s21_literal *target = NULL;
    // for (int i = 0; i < 10; i++) {
    //     d.id = i;
    //     if (i == 5) {
    //         printf("\n%d - remove\n", target->data.id);
    //         target = s21_pop(target);
    //     }
    //     target = s21_push(s21_init(d), target);
    //     printf("%p <-> ", target);
    // }
    // s21_literal *copy = target;
    // while (copy != NULL) {
    //     printf("%d -> ", copy->data.id);
    //     copy = copy->next;
    // }
    // while (target != NULL) {
    //     copy = target;
    //     free(target);
    //     target = copy->next;
    // }
    s21_literal *root_numbers = NULL;
    s21_literal *root_operands = NULL;
    char *string = "2 + 4E1e3 - 34.5 sin cos log mod";
    parse(string, root_numbers, root_operands);
    printf("%lf\n", atof("4E3"));
    s21_literal *cp = root_numbers;
    while (cp != NULL) {
        printf("%llf -> ", cp->data.value);
        cp = cp->next;
    }
}