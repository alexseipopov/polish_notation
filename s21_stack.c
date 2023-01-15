#include "s21_polish.h"

s21_literal *s21_push(struct data data, s21_literal *root) {
    static int id = 0;
    s21_literal *new = (s21_literal *)calloc(1, sizeof(s21_literal));
    data.id = id;
    new->data = data;
    new->next = root != NULL ? root : NULL;
    id++;
    return new;
}

s21_literal *s21_pop(s21_literal *root) {
    s21_literal *target = root;
    if (root != NULL) {
        target = root->next;
        free(root);
    }
    return target;
}
