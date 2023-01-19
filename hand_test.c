#include "s21_polish.h"

int main(void) {
    s21_literal *root_numbers = NULL;
    s21_literal *root_operands = NULL;
    double x = 33;
    char *string = "sin(90 / 57 ^ ^)*10";
    string = to_lower(string);
    parse(string, &root_numbers, &root_operands, x);
    while (root_operands != NULL) {
        counter(&root_numbers, &root_operands);
    }
    // root_operands->data.action(&root_numbers, &root_numbers);
    printf("%lf\n", root_numbers->data.value);
    print_stack(root_numbers);
}