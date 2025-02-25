#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// 将 Func 结构体转换为控制字符串，用于格式化输出
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

// 根据输入参数返回一个 Func 结构体
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
    // 如果转换成功，并且字符串以转义字符开头，则打印控制字符串
    if (func && func[0] == '\e')
    {
        printf("%s", func);
    }
    free(func);  
    va_start(args, format);
    retval = vprintf(format, args);
    va_end(args);
    // 打印结束控制符，重置控制台格式
    printf(NONE);
    return retval;
}
