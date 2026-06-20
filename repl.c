#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.tab.h"
#include "symtab.h"
#include "lex.yy.h"
#include "commands.h"

char last_input_line[1024];

static void process_line(const char *line) {
    YY_BUFFER_STATE buf = yy_scan_string(line);
    yyparse();
    yy_delete_buffer(buf);
}

static void process_pending_loadfunc(void) {
    if (!pending_loadfunc_file) return;

    FILE *f = fopen(pending_loadfunc_file, "r");
    if (!f) {
        printf("Error: cannot open %s\n", pending_loadfunc_file);
        free(pending_loadfunc_file);
        pending_loadfunc_file = NULL;
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        process_line(line);
    }

    fclose(f);
    printf("Loaded functions from %s\n", pending_loadfunc_file);

    free(pending_loadfunc_file);
    pending_loadfunc_file = NULL;
}

int main() {
    symtab_init();

    while (1) {
        printf(">>> ");

        if (!fgets(last_input_line, sizeof(last_input_line), stdin))
            break;

        process_line(last_input_line);
        process_pending_loadfunc();
    }
}
