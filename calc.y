%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "symtab.h"
    #include "builtins.h"
    #include "commands.h"
    #include "arglist.h"

    int yylex(void);
    int yyerror(char *s);
%}

%union {
    double num;
    char *id;
    struct ArgList *list;
}

%token <id> COMMAND IDENT
%token <num> NUMBER
%token PLUS TIMES MINUS DIVIDE
%token LPAREN RPAREN
%token EOL ASSIGN
%token COMMA

%type <num> expr term factor
%type <list> arglist

%left PLUS MINUS
%left TIMES DIVIDE
%right UMINUS

%start line

%%

line:
      expr EOL
        { printf("=%g\n", $1); }

    | IDENT ASSIGN expr EOL
        { assign_variable($1, $3); printf("=%g\n", $3); }

    | COMMAND IDENT EOL
        { handle_command_with_arg($1, $2); }

    | COMMAND EOL
        { handle_command($1); }

    | EOL
        { }
    ;

expr:
      expr PLUS term           { $$ = $1 + $3; }
    | expr MINUS term          { $$ = $1 - $3; }
    | term
    ;

term:
      term TIMES factor        { $$ = $1 * $3; }
    | term DIVIDE factor       { $$ = $1 / $3; }
    | factor
    ;

factor:
      MINUS factor %prec UMINUS { $$ = -$2; }
    | LPAREN expr RPAREN        { $$ = $2; }
    | NUMBER                    { $$ = $1; }
    | IDENT                     { $$ = lookup_variable($1); }
    | IDENT LPAREN arglist RPAREN
        { $$ = call_builtin_multi($1, $3); }
    ;

arglist:
      expr                     { $$ = arglist_prepend($1, NULL); }
    | expr COMMA arglist       { $$ = arglist_prepend($1, $3); }
    ;

%%

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}
