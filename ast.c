#include "ast.h"
#include "symtab.h"
#include "functab.h"
#include "builtins.h"
#include <stdlib.h>
#include <string.h>

Ast *ast_num(double v) {
    Ast *n = malloc(sizeof(Ast));
    n->kind = AST_NUM;
    n->u.num = v;
    return n;
}

Ast *ast_var(char *name) {
    Ast *n = malloc(sizeof(Ast));
    n->kind = AST_VAR;
    n->u.var = name;
    return n;
}

Ast *ast_bin(int op, Ast *l, Ast *r) {
    Ast *n = malloc(sizeof(Ast));
    n->kind = AST_BINOP;
    n->u.bin.op = op;
    n->u.bin.left = l;
    n->u.bin.right = r;
    return n;
}

ArgListAst *arglist_ast_prepend(Ast *e, ArgListAst *rest) {
    ArgListAst *n = malloc(sizeof(ArgListAst));
    n->expr = e;
    n->next = rest;
    return n;
}

Ast *ast_call(char *name, ArgListAst *args) {
    Ast *n = malloc(sizeof(Ast));
    n->kind = AST_CALL;
    n->u.call.name = name;
    n->u.call.args = args;
    return n;
}

static double eval_ast_internal(Ast *node);

static double eval_call(const char *name, ArgListAst *args) {
    /* evaluate args to a runtime ArgList for builtins / user funcs */
    ArgList *runtime_args = NULL;
    for (ArgListAst *p = args; p; p = p->next) {
        double v = eval_ast_internal(p->expr);
        runtime_args = arglist_prepend(v, runtime_args);
    }

    Function *fn = functab_lookup(name);
    if (fn) {
        /* bind params, eval body AST, unbind (you can add simple scoping later) */
        ParamList *p = fn->params;
        ArgList *a = runtime_args;
        while (p && a) {
            assign_variable(p->name, a->value);
            p = p->next;
            a = a->next;
        }
        return eval_ast_internal(fn->body);
    } else {
        return call_builtin_multi(name, runtime_args);
    }
}

static double eval_ast_internal(Ast *node) {
    switch (node->kind) {
    case AST_NUM:
        return node->u.num;
    case AST_VAR:
        return lookup_variable(node->u.var);
    case AST_BINOP: {
        double l = eval_ast_internal(node->u.bin.left);
        double r = eval_ast_internal(node->u.bin.right);
        switch (node->u.bin.op) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return l / r;
        }
    }
    case AST_CALL:
        return eval_call(node->u.call.name, node->u.call.args);
    }
    return 0;
}

double eval_ast(Ast *node) {
    return eval_ast_internal(node);
}
