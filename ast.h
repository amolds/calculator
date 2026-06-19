/* ast.h */

#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUM,
    AST_VAR,
    AST_BINOP,
    AST_CALL
} AstKind;

typedef struct Ast Ast;

struct Ast {
    AstKind kind;
    union {
        double num;
        char *var;
        struct {
            int op;
            Ast *left;
            Ast *right;
        } bin;
        struct {
            char *name;
            struct ArgListAst *args;
        } call;
    } u;
};

typedef struct ArgListAst {
    Ast *expr;
    struct ArgListAst *next;
} ArgListAst;

Ast *ast_num(double v);
Ast *ast_var(char *name);
Ast *ast_bin(int op, Ast *l, Ast *r);
Ast *ast_call(char *name, ArgListAst *args);

ArgListAst *arglist_ast_prepend(Ast *e, ArgListAst *rest);

double eval_ast(Ast *node);

#endif
