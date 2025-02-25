#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *funcToString(Func f)
{
    char *func = calloc(20, sizeof(char));
    if (func == NULL)
    {
        return NULL;
    }
    snprintf(func, 20, "\e[%s%s%s%s%s%s",
             f.control, SEMICOLON, f.front,
             SEMICOLON, f.back, END);
    return func;
}

Func getFunc(char *control, char *front, char *back)
{
    Func f = {control, front, back};
    return f;
}

int print(Func f, const char *format, ...)
{
    int retval;
    va_list args;
    char *func = funcToString(f);
    if (func && func[0] == '\e')
    {
        printf("%s", func);
    }
    free(func);
    va_start(args, format);
    retval = vprintf(format, args);
    va_end(args);
    printf(NONE);

    return retval;
}
