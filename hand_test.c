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
    struct data data;
    data.value = 10;
    root_numbers = s21_push(data, root_numbers);
    s21_pop(root_numbers);
    char *string = "cos 30";
    string = to_lower(string);
    parse(string, &root_numbers, &root_operands);
    root_numbers->data.action(root_numbers, root_numbers);
    // printf("%lf\n", atof("4E-2"));
    // print_stack(root_numbers);
    // string = to_lower(string);
    // printf("%s\n", string);
    // s21_literal *root = NULL;
    // struct data data = {0};
    // for (int i = 0; i < 10; i++) {
    //     data.value = i;
    //     root = s21_push(data, root);
    // }
    // for (int i = 0; i < 5; i++) {
    //     root = s21_pop(root);
    // }
    // print_stack(root);
}