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

void functab_store(FILE *f) {
    for (int i = 0; i < func_count; i++) {
        Function *fn = &funcs[i];

        fprintf(f, "def %s(", fn->name);

        ParamList *p = fn->params;
        while (p) {
            fprintf(f, "%s", p->name);
            if (p->next) fprintf(f, ", ");
            p = p->next;
        }

        fprintf(f, ") = ");
        ast_print(fn->body, f);
        fprintf(f, "\n");
    }
}

void functab_dump() {
    for (int i = 0; i < func_count; i++) {
        Function *fn = &funcs[i];

        printf("def %s(", fn->name);

        ParamList *p = fn->params;
        while (p) {
            printf("%s", p->name);
            if (p->next) printf(", ");
            p = p->next;
        }

        printf(") = ");
        ast_print(fn->body, stdout);
        printf("\n");
    }
}

void functab_clear() {
    func_count = 0;
}