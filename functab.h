/* functab.h */

#ifndef FUNCTAB_H
#define FUNCTAB_H

#include "paramlist.h"
#include "ast.h"

typedef struct Function {
    char *name;
    ParamList *params;
    Ast *body;
} Function;

void functab_define(const char *name, ParamList *params, Ast *body);
Function *functab_lookup(const char *name);

#endif
