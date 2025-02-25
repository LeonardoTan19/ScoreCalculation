#include <stdio.h>
#include "menu.h"
#include "store.h"
#include "stdlib.h"
EventList events = NULL;
SchoolList schools = NULL;


int main()
{
    events = EventList_Init();
    schools = SchoolList_Init();
    fullLoad(events, schools);
    calculateScore(events, schools);
    printWelcome();
    while (1)
    {
        mainMenu()();
    }
    return 0;
}