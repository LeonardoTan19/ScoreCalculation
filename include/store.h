#ifndef _STORE_H
#define _STORE_H
#include "prehead.h"
#include "event.h"
#include "school.h"
#include "stdio.h"
#include "stdlib.h"
extern EventList events;
extern SchoolList schools;
int fullSave(EventList events, SchoolList schools);
int fullLoad(EventList events, SchoolList schools);
int calculateScore(EventList events, SchoolList schools);
#endif