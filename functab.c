/* functab.c */

#include "functab.h"
#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_FUNCS 128

static Function funcs[MAX_FUNCS];
static int func_count = 0;

void functab_define(const char *name, ParamList *params, Ast *body) {
    if (func_count >= MAX_FUNCS) {
        printf("Error: function table full\n");
        return;
    }

    funcs[func_count].name = strdup(name);
    funcs[func_count].params = params;
    funcs[func_count].body = body;
    func_count++;
}

Function *functab_lookup(const char *name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(funcs[i].name, name) == 0) {
            return &funcs[i];
        }
    }

    return NULL;
}
