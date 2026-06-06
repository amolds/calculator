#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>   // <-- REQUIRED for FILE*

typedef struct {
    char *name;
    double value;
} Var;

void symtab_init(void);
Var *find_var(const char *name);
Var *get_or_create_var(const char *name);
double lookup_variable(const char *name);
void assign_variable(const char *name, double value);
void symtab_dump(void);
void symtab_clear(void);
void symtab_store(FILE *f);
void symtab_load(FILE *f);

#endif
