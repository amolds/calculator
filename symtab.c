#define _GNU_SOURCE
#define _USE_MATH_DEFINES

#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_VARS 256

static Var vars[MAX_VARS];
static int var_count = 0;

void symtab_init(void) {
    var_count = 0;

    /* Built‑in constants */
    assign_variable("pi", M_PI);
    assign_variable("e",  M_E);
}

Var *find_var(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0)
            return &vars[i];
    }
    return NULL;
}

Var *get_or_create_var(const char *name) {
    Var *v = find_var(name);
    if (v) return v;

    if (var_count >= MAX_VARS) {
        fprintf(stderr, "Symbol table full\n");
        exit(1);
    }

    vars[var_count].name = strdup(name);
    vars[var_count].value = 0;
    return &vars[var_count++];
}

double lookup_variable(const char *name) {
    Var *v = find_var(name);
    if (!v) {
        printf("Error: undefined variable '%s'\n", name);
        return 0;
    }
    return v->value;
}

void assign_variable(const char *name, double value) {
    Var *v = get_or_create_var(name);
    v->value = value;
}

void symtab_dump(void) {
    printf("Symbols:\n");
    for (int i = 0; i < var_count; i++) {
        printf("  %s = %g\n", vars[i].name, vars[i].value);
    }
}

void symtab_clear(void) {
    var_count = 0;
}

void symtab_store(FILE *f) {
    for (int i = 0; i < var_count; i++) {
        fprintf(f, "%s %g\n", vars[i].name, vars[i].value);
    }
}

void symtab_load(FILE *f) {
    symtab_clear();

    char name[256];
    double value;

    while (fscanf(f, "%255s %lf", name, &value) == 2) {
        assign_variable(name, value);
    }
}
