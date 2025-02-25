#include "prehead.h"
Func LIST_FUNC = {C_DEFAULT, F_GREEN, B_DEFAULT};
Func ERROR_FUNC = {C_BOLD, F_RED, B_DEFAULT};
Func PROMPT_FUNC = {C_BOLD, F_DEFAULT, B_DEFAULT};
Func SUCCESS_FUNC = {C_BOLD, F_GREEN, B_DEFAULT};
bool isDataChange = false;
int getValidNumInput(const char *prompt, int min, int max)
{
    int output = 0;
    char input[1024];
    while (1)
    {
        print(PROMPT_FUNC, "%s", prompt);
        scanf("%s", input);
        if (sscanf(input, "%d", &output) == 1 && output >= min && output <= max)
        {
            break;
        }
        print(ERROR_FUNC, "错误的输入！\n");
    }
    return output;
}