#ifndef ARGLIST_H
#define ARGLIST_H

#include <stdlib.h>   // <-- REQUIRED for malloc()

typedef struct ArgList {
    double value;
    struct ArgList *next;
} ArgList;

static inline ArgList *arglist_prepend(double v, ArgList *rest) {
    ArgList *n = malloc(sizeof(ArgList));
    n->value = v;
    n->next = rest;
    return n;
}

#endif
