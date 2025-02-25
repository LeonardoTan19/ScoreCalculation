#ifndef _EVENT_H_
#define _EVENT_H_
#include "prehead.h"
#include "list.h"
#include "result.h"


extern int nextEventId;
typedef struct Event
{
    int id;
    char name[MAX_LENTH_NAME];
    ComType comType;
    ScoreType scoreType;
    ResultList results;
} Event;

// 初始化项目列表，提供接口
List(Event)

// 项目比较函数
int event_CmpById(const Event *a, const Event *b);
// 项目信息
char* eventInfo(const Event event,char end);
// 项目简略信息
char* eventInfo_Short(const Event event,char end);
// 项目结果转换为分数
int resultToScore(const Event event, const Result result);
// 创建项目
Event createEvent(char* name,ComType comType,ScoreType scoreType);
// 打印所有项目
int printEvents(const EventList events);
// 修改项目
void modifyEvent(const EventList events);
// 录入项目
void inputEvent(const EventList events);
// 录入比赛结果
void inputResult(const EventList events);
// 修改比赛结果
void modifyResult(const EventList events);
// 搜索项目结果（0为根据项目id，1为根据学校id）
void searchEventResult(const int byWhat, const int id, const EventList events);
#endif