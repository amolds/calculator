#include "commands.h"
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_command_with_arg(const char *cmd, const char *arg) {
    if (strcmp(cmd, ":store") == 0) {
        FILE *f = fopen(arg, "w");
        if (!f) {
            printf("Error: cannot open %s for writing\n", arg);
            return;
        }

        symtab_store(f);
        fclose(f);
        printf("Stored variables to %s\n", arg);
    }

    else if (strcmp(cmd, ":load") == 0) {
        FILE *f = fopen(arg, "r");
        if (!f) {
            printf("Error: cannot open %s for reading\n", arg);
            return;
        }

        symtab_load(f);
        fclose(f);
        printf("Loaded variables from %s\n", arg);
    }
}

void handle_command(const char *cmd) {
    if (strcmp(cmd, ":symbols") == 0 ||
        strcmp(cmd, ":vars") == 0 ||
        strcmp(cmd, ":dump") == 0) {

        symtab_dump();
    }

    else if (strcmp(cmd, ":reset") == 0) {
        symtab_clear();
        printf("All variables cleared.\n");
    }

    else if (strcmp(cmd, ":help") == 0) {
        printf("Available commands:\n");
        printf("  :symbols        Show all variables\n");
        printf("  :reset          Clear all variables\n");
        printf("  :store <file>   Save variables to a file\n");
        printf("  :load <file>    Load variables from a file\n");
        printf("  :help           Show this help message\n");
        printf("  :quit           Exit the interpreter\n");
    }

    else if (strcmp(cmd, ":quit") == 0) {
        exit(0);
    }

    else {
        printf("Unknown command: %s\n", cmd);
    }
}
