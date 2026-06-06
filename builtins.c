#include "builtins.h"
#include "arglist.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Single‑argument builtins */
double call_builtin(const char *name, double arg) {

    if (strcmp(name, "abs") == 0)   return fabs(arg);
    if (strcmp(name, "sqrt") == 0)  return sqrt(arg);
    if (strcmp(name, "exp") == 0)   return exp(arg);
    if (strcmp(name, "log") == 0)   return log(arg);
    if (strcmp(name, "log10") == 0) return log10(arg);

    if (strcmp(name, "sin") == 0)   return sin(arg);
    if (strcmp(name, "cos") == 0)   return cos(arg);
    if (strcmp(name, "tan") == 0)   return tan(arg);

    if (strcmp(name, "ceil") == 0)  return ceil(arg);
    if (strcmp(name, "floor") == 0) return floor(arg);
    if (strcmp(name, "round") == 0) return round(arg);

    printf("Error: unknown function '%s'\n", name);
    return 0;
}

/* Multi‑argument builtins */
double call_builtin_multi(const char *name, ArgList *args) {

    /* Count args */
    int count = 0;
    for (ArgList *p = args; p; p = p->next)
        count++;

    /* Single‑argument functions use the old dispatcher */
    if (count == 1)
        return call_builtin(name, args->value);

    /* Multi‑argument functions */
    if (strcmp(name, "pow") == 0) {
        if (count != 2) {
            printf("Error: pow() takes exactly 2 arguments\n");
            return 0;
        }
        return pow(args->value, args->next->value);
    }

    printf("Error: unknown multi‑argument function '%s'\n", name);
    return 0;
}
