#include "s21_polish.h"

double my_unar_minus(double target) { return target * -1; }

double my_unar_plus(double target) { return target; }

int s21_do_cos(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &cos);
}

int s21_do_sin(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &sin);
}

int s21_do_tan(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &tan);
}

int s21_do_acos(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &acos);
}

int s21_do_asin(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &asin);
}

int s21_do_atan(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &atan);
}

int s21_do_sqrt(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &sqrt);
}

int s21_do_ln(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &log);
}

int s21_do_log(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &log10);
}

int unar_minus(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &my_unar_minus);
}

int unar_plus(unit **numbers, unit **operators) {
    return unar_action(numbers, operators, &my_unar_plus);
}

double my_plus(double first, double second) { return first + second; }

double my_minus(double first, double second) { return first - second; }

double my_mult(double first, double second) { return first * second; }

double my_div(double first, double second) { return first / second; }

int s21_do_plus(unit **numbers, unit **operators) {
    return binar_action(numbers, operators, &my_plus);
}

int s21_do_minus(unit **numbers, unit **operators) {
    return binar_action(numbers, operators, &my_minus);
}

int s21_do_div(unit **numbers, unit **operators) {
    return binar_action(numbers, operators, &my_div);
}

int s21_do_mult(unit **numbers, unit **operators) {
    return binar_action(numbers, operators, &my_mult);
}

int s21_do_mod(unit **numbers, unit **operators) {
    return binar_action(numbers, operators, &fmod);
}

int s21_do_pow(unit **numbers, unit **operators) {
    return binar_action(numbers, operators, &pow);
}