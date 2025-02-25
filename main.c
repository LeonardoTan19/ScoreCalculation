#include <stdio.h>
#include "menu.h"
#include "store.h"
#include "stdlib.h"
EventList events = NULL;
SchoolList schools = NULL;


int main()
{
    // 更改控制台编码
    system("chcp 65001&cls");
    // 载入数据
    events = EventList_Init();
    schools = SchoolList_Init();
    fullLoad(events, schools);
    calculateScore(events, schools);
    printWelcome();
    // 进入主菜单
    while (1)
    {
        mainMenu()();
    }
    return 0;
}