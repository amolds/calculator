#include "commands.h"
#include "symtab.h"
#include "functab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pending_loadfunc_file = NULL;

void handle_command_with_arg(const char *cmd, const char *arg) {

    if (strcmp(cmd, ":store") == 0) {
        FILE *f = fopen(arg, "w");
        if (!f) { printf("Error: cannot open %s\n", arg); return; }
        symtab_store(f);
        fclose(f);
        printf("Stored variables to %s\n", arg);
    }

    else if (strcmp(cmd, ":load") == 0) {
        FILE *f = fopen(arg, "r");
        if (!f) { printf("Error: cannot open %s\n", arg); return; }
        symtab_load(f);
        fclose(f);
        printf("Loaded variables from %s\n", arg);
    }

    else if (strcmp(cmd, ":storefunc") == 0) {
        FILE *f = fopen(arg, "w");
        if (!f) { printf("Error: cannot open %s\n", arg); return; }
        functab_store(f);
        fclose(f);
        printf("Stored functions to %s\n", arg);
    }

    else if (strcmp(cmd, ":loadfunc") == 0) {
        free(pending_loadfunc_file);
        pending_loadfunc_file = strdup(arg);
        /* actual loading happens in REPL */
    }
}

void handle_command(const char *cmd) {
    if (strcmp(cmd, ":symbols") == 0 ||
        strcmp(cmd, ":vars") == 0 ||
        strcmp(cmd, ":dump") == 0) {
        symtab_dump();
    }

    else if (strcmp(cmd, ":functions") == 0 ||
         strcmp(cmd, ":funcs") == 0) {
        functab_dump();
    }

    else if (strcmp(cmd, ":reset") == 0) {
        symtab_clear();
        printf("All variables cleared.\n");
    }

    else if (strcmp(cmd, ":resetfuncs") == 0) {
        functab_clear();
        printf("All functions cleared.\n");
    }

    else if (strcmp(cmd, ":help") == 0) {
        printf("Commands:\n");
        printf("  :symbols\n");
        printf("  :functions\n");
        printf("  :reset\n");
        printf("  :resetfuncs\n");
        printf("  :store <file>\n");
        printf("  :load <file>\n");
        printf("  :storefunc <file>\n");
        printf("  :loadfunc <file>\n");
        printf("  :quit\n");
    }

    else if (strcmp(cmd, ":quit") == 0) {
        exit(0);
    }

    else {
        printf("Unknown command: %s\n", cmd);
    }
}
