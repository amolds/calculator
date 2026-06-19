/* paramlist.h */

#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include <stdlib.h>

typedef struct ParamList {
    char *name;
    struct ParamList *next;
} ParamList;

static inline ParamList *paramlist_prepend(char *name, ParamList *rest) {
    ParamList *p = malloc(sizeof(ParamList));
    p->name = name;
    p->next = rest;
    return p;
}

#endif
