/* builtins.c */

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

    /* min(x, y, ...) */
    if (strcmp(name, "min") == 0) {
        if (count < 1) {
            printf("Error: min() requires at least 1 argument\n");
            return 0;
        }
        double m = args->value;
        for (ArgList *p = args->next; p; p = p->next)
            if (p->value < m) m = p->value;
        return m;
    }

    /* max(x, y, ...) */
    if (strcmp(name, "max") == 0) {
        if (count < 1) {
            printf("Error: max() requires at least 1 argument\n");
            return 0;
        }
        double m = args->value;
        for (ArgList *p = args->next; p; p = p->next)
            if (p->value > m) m = p->value;
        return m;
    }

    /* sum(x, y, ...) */
    if (strcmp(name, "sum") == 0) {
        double s = 0;
        for (ArgList *p = args; p; p = p->next)
            s += p->value;
        return s;
    }

    printf("Error: unknown multi‑argument function '%s'\n", name);
    return 0;
}
