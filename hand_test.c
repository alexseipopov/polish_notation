#include "s21_polish.h"

int main(void) {
    unit *result = NULL;
    unit *root_operands = NULL;
    // double x = 33;
    char *string = "9x + 1";
    string = to_lower(string);
    int status = parse(string, &result, &root_operands);
    if (status == SUCCESS) {
        printf("%lf\n", result->data.value);
        print_stack(result);
    } else {
        print_problem(status);
    }
}