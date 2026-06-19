%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "symtab.h"
    #include "builtins.h"
    #include "commands.h"
    #include "ast.h"
    #include "arglist.h"
    #include "paramlist.h"
    #include "functab.h"

    int yylex(void);
    int yyerror(char *s);
%}

%code requires {
    #include "ast.h"
    #include "arglist.h"
    #include "paramlist.h"    
}

%union {
    double num;
    char *id;
    ArgList *list;
    ParamList *plist;
    Ast *ast;
    ArgListAst *alist;
}

%token <id> COMMAND IDENT
%token <num> NUMBER
%token PLUS TIMES MINUS DIVIDE
%token LPAREN RPAREN
%token EOL ASSIGN
%token COMMA
%token DEF

%type <ast> expr term factor
%type <alist> arglist
%type <plist> paramlist

%left PLUS MINUS
%left TIMES DIVIDE
%right UMINUS

%start line

%%

line:
      assignment EOL
    | expr EOL
        {
            last_result = eval_ast($1);
            printf("=%g\n", last_result);
        }
    | COMMAND IDENT EOL
        { handle_command_with_arg($1, $2); }
    | COMMAND EOL
        { handle_command($1); }
    | EOL
        { }
    ;

assignment:
      IDENT ASSIGN expr
        {
            double v = eval_ast($3);
            assign_variable($1, v);
            last_result = v;
            printf("=%g\n", v);
        }
    | DEF IDENT LPAREN paramlist RPAREN ASSIGN expr
        {
            functab_define($2, $4, $7);
            printf("Defined function %s\n", $2);
        }
    ;

expr:
      expr PLUS term      { $$ = ast_bin('+', $1, $3); }
    | expr MINUS term     { $$ = ast_bin('-', $1, $3); }
    | term                { $$ = $1; }
    ;

term:
      term TIMES factor   { $$ = ast_bin('*', $1, $3); }
    | term DIVIDE factor  { $$ = ast_bin('/', $1, $3); }
    | factor              { $$ = $1; }
    ;

factor:
      MINUS factor %prec UMINUS { $$ = ast_bin('-', ast_num(0), $2); }
    | LPAREN expr RPAREN        { $$ = $2; }
    | NUMBER                    { $$ = ast_num($1); }
    | IDENT                     { $$ = ast_var($1); }
    | IDENT LPAREN arglist RPAREN
        { $$ = ast_call($1, $3); }
    ;

arglist:
      expr                 { $$ = arglist_ast_prepend($1, NULL); }
    | expr COMMA arglist   { $$ = arglist_ast_prepend($1, $3); }
    ;

paramlist:
      IDENT                     { $$ = paramlist_prepend($1, NULL); }
    | IDENT COMMA paramlist     { $$ = paramlist_prepend($1, $3); }
    ;

%%

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}
