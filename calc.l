%{
    #include "calc.tab.h"
    #include <string.h>
    #include <stdlib.h>
%}

%%

":"[a-zA-Z_]+               { yylval.id = strdup(yytext); return COMMAND; }
[a-zA-Z_][a-zA-Z0-9_]*      { yylval.id = strdup(yytext); return IDENT; }
[0-9]+(\.[0-9]+)?           { yylval.num = atof(yytext); return NUMBER; }
[ \t]+                      { }
\n                          { return EOL; }

"="                         { return ASSIGN; }
"+"                         { return PLUS; }
"*"                         { return TIMES; }
"-"                         { return MINUS; }
"/"                         { return DIVIDE; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
","                         { return COMMA; }

.                           { }

%%
