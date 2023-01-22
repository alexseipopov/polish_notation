#include "s21_polish.h"

int main(void) {
    unit *result = NULL;
    unit *root_operands = NULL;
    double x = 33;
    double res;
    char *string = "sin 4 + 3 /2 - sqrt(4) +-1 ";
    string = to_lower(string);
    int status = parse(string, &result, &root_operands);
    if (status == SUCCESS) {
        resolve_struct(&result, x, &res);
        printf("%lf\n", res);
        // print_stack(result);
    } else {
        print_problem(status);
    }
}