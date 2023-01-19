#include "s21_polish.h"

unit *s21_push(struct data data, unit *root) {
    static int id = 0;
    unit *new = (unit *)calloc(1, sizeof(unit));
    data.id = id;
    new->data = data;
    new->next = root != NULL ? root : NULL;
    id++;
    return new;
}

unit *s21_pop(unit *root) {
    unit *target = root;
    if (root != NULL) {
        target = root->next;
        free(root);
    }
    return target;
}
