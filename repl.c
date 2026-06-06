#include <stdio.h>
#include "calc.tab.h"
#include "symtab.h"
#include "lex.yy.h"

int main() {
    symtab_init();

    char line[1024];

    while (1) {
        printf(">>> ");
        if (!fgets(line, sizeof(line), stdin))
            break;

        YY_BUFFER_STATE buf = yy_scan_string(line);
        yyparse();
        yy_delete_buffer(buf);
    }
}
