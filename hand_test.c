#include "s21_polish.h"

int main(void) {
    char *string = "+-/3";
    double res;
    int status;
    for (int i = 0; i < 2; i++) {
        status = s21_solve_result(string, 0, &res);
    }

    printf("%lf\t%d\n", res, status);
    // free(string);
}