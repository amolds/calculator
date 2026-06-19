/* repl.c */

#include <stdio.h>
#include "calc.tab.h"
#include "symtab.h"
#include "lex.yy.h"

char last_input_line[1024];

int main() {
    symtab_init();

    while (1) {
        printf(">>> ");

        if (!fgets(last_input_line, sizeof(last_input_line), stdin))
            break;

        YY_BUFFER_STATE buf = yy_scan_string(last_input_line);
        yyparse();
        yy_delete_buffer(buf);
    }
}
