#include "s21_polish.h"

// s21_literal *s21_create_root(struct data data) {
//     s21_literal *root = (s21_literal *)calloc(1, sizeof(s21_literal));
//     root->next = NULL;
//     root->data = data;
//     return root;
// }

s21_literal *s21_push(s21_literal *target, s21_literal *root) {
    if (root != NULL) target->next = root;
    root = target;
    return root;
}

s21_literal *s21_pop(s21_literal *root) {
    s21_literal *target = root;
    if (root != NULL) {
        target = root->next;
        free(root);
    }
    return target;
}