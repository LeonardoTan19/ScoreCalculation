#include "event.h"
#include "stdio.h"
#include "stdlib.h"
#include "store.h"

int nextEventId = 1;

int event_CmpById(const Event *a, const Event *b)
{
    return a->id - b->id;
}

char *eventInfo(const Event event, char end)
{
    char *str = (char *)calloc(MAX_LENTH_NAME + 70, sizeof(char));
    snprintf(str, MAX_LENTH_NAME + 70, "ID：%-4d %s 比赛类型：%10s 计分方式：%-8s%c",
             event.id, event.name, getComType(event.comType), getScoreType(event.scoreType), end);
    return str;
}

char *eventInfo_Short(const Event event, char end)
{
    char *str = (char *)calloc(MAX_LENTH_NAME + 50, sizeof(char));
    snprintf(str, MAX_LENTH_NAME + 5, "%s%c", event.name, end);
    return str;
}

int resultToScore(const Event event, const Result result)
{
    if (topFive == event.scoreType)
        // 若排名大于第五名，得分为0，否则从ScoreFive表中获取分数
        return getResultRank(event.results, result) > 4 ? 0 : ScoreFive[getResultRank(event.results, result)];
    else
        // 若排名大于第三名，得分为0，否则从ScoreThree表中获取分数
        return getResultRank(event.results, result) > 2 ? 0 : ScoreThree[getResultRank(event.results, result)];
}

Event createEvent(char *name, ComType comType, ScoreType scoreType)
{
    Event event;
    event.id = nextEventId++;
    memset(event.name, 0, MAX_LENTH_NAME);
    strncat(event.name, name, MAX_LENTH_NAME - 1);
    event.comType = comType;
    event.scoreType = scoreType;
    event.results = ResultList_Init();
    return event;
}

int printEvents(const EventList events)
{
    if (events && events->head)
    {
        print(getFunc(C_BOLD, F_BLUE, B_DEFAULT), "项目信息\n");
        print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "排名 项目名称 项目类型 计分方式 \n");
        print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "---- --------- ---------- ----------\n");
        for (EventNode *eventNode = events->head; eventNode; eventNode = eventNode->next)
        {
            // 简要显示每个项目的信息
            printf("%-4d %s %10s %-8s\n",
                   eventNode->data.id,
                   eventInfo_Short(eventNode->data, '\0'),
                   getComType(eventNode->data.comType),
                   getScoreType(eventNode->data.scoreType));
        }
    }
    else
    {
        print(ERROR_FUNC, "没有项目信息可显示\n");
    }
    return events->size;
}

void modifyEvent(const EventList events)
{
    int id;
    if (printEvents(events) == 0)
        return;
    id = getValidNumInput("请输入要修改的项目编号：", 1, events->size);
    EventNode *eventNode = EventList_Get(events, id - 1);
    if (eventNode)
    {
        print(PROMPT_FUNC, "请输入新的项目名称（输入#删除该项目）：");
        char name[MAX_LENTH_NAME];
        getchar();
        fgets(name, MAX_LENTH_NAME - 1, stdin);
        name[strlen(name) - 1] = '\0';
        if (strcmp(name, "#") == 0)
        {
            // 将该项目删除后，重置其他项目的ID
            EventList_Delete(events, id - 1);
            print(PROMPT_FUNC, "项目删除成功！\n");
            isDataChange = true;
            int newId = 1;
            for (EventNode *node = events->head; node; node = node->next)
            {
                node->data.id = newId++;
            }
        }
        else
        {
            // 修改指定项目的类型、计分方式并刷新ID
            const char *comTypePrompts = "请输入项目类型（1. 男子径赛 2. 男子田赛 3. 女子径赛 4. 女子田赛）：";
            const char *scoreTypePrompts = "请输入计分方式（1. 前三名 2. 前五名）：";
            ComType comType = getValidNumInput(comTypePrompts, 1, 4);
            ScoreType scoreType = getValidNumInput(scoreTypePrompts, 1, 2);
            memset(eventNode->data.name, 0, MAX_LENTH_NAME);
            strncat(eventNode->data.name, name, MAX_LENTH_NAME - 1);
            eventNode->data.comType = comType;
            eventNode->data.scoreType = scoreType;
            int newId = 1;
            for (EventNode *node = events->head; node; node = node->next)
            {
                node->data.id = newId++;
            }
            print(PROMPT_FUNC, "项目修改成功！\n");
            isDataChange = true;
        }
    }
    else
    {
        print(ERROR_FUNC, "没有找到该项目！\n");
    }
}

void inputEvent(const EventList events)
{
    int count;
    count = getValidNumInput("请输入要录入的项目数量（0以取消）：", 0, MAX_EVENT - events->size);
    for (int i = 0; i < count; i++)
    {
        print(getFunc(C_BOLD, F_BLUE, B_YELLOW), "【录入第%d项】", i + 1);
        print(PROMPT_FUNC, "请输入项目名称：");
        char name[MAX_LENTH_NAME];
        getchar();
        fgets(name, MAX_LENTH_NAME - 1, stdin);
        name[strlen(name) - 1] = '\0';
        const char *comTypePrompts = "请输入项目类型（1. 男子径赛 2. 男子田赛 3. 女子径赛 4. 女子田赛）：";
        const char *scoreTypePrompts = "请输入计分方式（1. 前三名 2. 前五名）：";
        ComType comType = getValidNumInput(comTypePrompts, 1, 4);
        ScoreType scoreType = getValidNumInput(scoreTypePrompts, 1, 2);
        // 将新建的赛事插入到链表尾部
        EventList_Insert_Tail(events, createEvent(name, comType, scoreType));
        print(PROMPT_FUNC, "项目录入成功！\n");
        isDataChange = true;
    }
}

void inputResult(const EventList events)
{
    int count;
    if (printEvents(events) == 0)
        return;
    int id = getValidNumInput("请输入要录入成绩的项目编号：", 1, events->size);
    EventNode *eventNode = EventList_Get(events, id - 1);
    count = getValidNumInput("请输入要录入的数量（0以取消）：", 0, MAX_EVENT - events->size);
    printSchools(schools);
    for (int i = 0; i < count; i++)
    {
        print(getFunc(C_BOLD, F_BLUE, B_YELLOW), "【录入第%d项】", i + 1);
        if (eventNode)
        {
            int schoolId;
            schoolId = getValidNumInput("请输入学校编号：", 1, schools->size);
            SchoolNode *schoolNode = SchoolList_Get(schools, schoolId - 1);
            if (schoolNode)
            {
                // 不断提示用户输入成绩，直到获取正确格式的成绩
                while (1)
                {
                    char gradeString[MAX_LENTH_RESULT];
                    print(PROMPT_FUNC, eventNode->data.comType % 2 ? "请输入时间（-h--'--\"--[可不输入大单位]）：" : "请输入距离（-.--m）：");
                    getchar();
                    fgets(gradeString, MAX_LENTH_RESULT - 1, stdin);
                    gradeString[strlen(gradeString) - 1] = '\0';
                    int grade = stringToResult(eventNode->data.comType, gradeString);
                    if (grade != -1)
                    {
                        ResultList_Insert_Head(eventNode->data.results, createResult(schoolNode->data, grade));
                        print(PROMPT_FUNC, "成绩录入成功！\n");
                        isDataChange = true;
                        break;
                    }
                    else
                    {
                        print(ERROR_FUNC, "成绩录入失败！请检查您的输入。\n");
                    }
                }
            }
            else
            {
                print(ERROR_FUNC, "没有找到该学校！\n");
            }
        }
        else
        {
            print(ERROR_FUNC, "没有找到该项目！\n");
        }

        // 对录入的成绩进行排序
        ResultList_Sort(eventNode->data.results,
                        eventNode->data.comType % 2 ? result_CmpByGrade_Track : result_CmpByGrade_Field);
    }
}

void modifyResult(const EventList events)
{
    int id;
    if (printEvents(events) == 0)
    {
        print(ERROR_FUNC, "没有项目信息可显示\n");
        return;
    }
    id = getValidNumInput("请输入要修改成绩的项目编号（0以取消）：", 0, events->size);
    if (id == 0)
        return;
    EventNode *eventNode = EventList_Get(events, id - 1);
    if (eventNode)
    {
        print(getFunc(C_BOLD, F_BLUE, B_DEFAULT), "序号 学校名称 成绩（得分）\n");
        print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "---- ----------- --------\n");
        ResultNode *resultNode = eventNode->data.results->head;
        for (int i = 0; i < eventNode->data.results->size; i++)
        {
            if (resultNode)
            {
                printf("%-4d %-*s %s（%d）\n",
                       i + 1,
                       MAX_LENTH_NAME - 1,
                       resultNode->data.school.name,
                       resultToString(eventNode->data.comType, resultNode->data, '\0'),
                       resultToScore(eventNode->data, resultNode->data));
                resultNode = resultNode->next;
            }
            else
            {
                print(ERROR_FUNC, "未找到相关的成绩！\n");
            }
        }
        int rank;
        rank = getValidNumInput("请输入要修改的成绩序号（0以取消）：", 0, eventNode->data.results->size);
        getchar();
        if (rank == 0)
            return;
        ResultNode *resultNodeToModify = ResultList_Get(eventNode->data.results, rank - 1);
        if (resultNodeToModify)
        {
            // 提示用户输入新成绩或删除成绩
            while (1)
            {
                char gradeString[MAX_LENTH_RESULT];
                print(PROMPT_FUNC,
                      eventNode->data.comType % 2 ? "请输入时间（-h--'--''--[可不输入大单位]）（#以删除）：" : "请输入距离（-.--m）：");
                fgets(gradeString, MAX_LENTH_RESULT - 1, stdin);
                gradeString[strlen(gradeString) - 1] = '\0';
                if (strcmp(gradeString, "#") == 0)
                {
                    ResultList_Delete(eventNode->data.results, rank - 1);
                    ResultList_Sort(eventNode->data.results,
                                    eventNode->data.comType % 2 ? result_CmpByGrade_Track : result_CmpByGrade_Field);
                    print(PROMPT_FUNC, "成绩删除成功！\n");
                    isDataChange = true;
                    break;
                }
                else
                {
                    int grade = stringToResult(eventNode->data.comType, gradeString);
                    if (grade != -1)
                    {
                        resultNodeToModify->data.grade = grade;
                        ResultList_Sort(eventNode->data.results,
                                        eventNode->data.comType % 2 ? result_CmpByGrade_Track : result_CmpByGrade_Field);
                        print(PROMPT_FUNC, "成绩修改成功！\n");
                        isDataChange = true;
                        break;
                    }
                    else
                    {
                        print(ERROR_FUNC, "成绩录入失败！请检查您的输入。\n");
                    }
                }
            }
        }
    }
}

void printEventResult(const EventList events)
{
    int byWhat = getValidNumInput("请输入查询方式（1.按项目查询 2.按学校查询）：", 1, 2), id;
    if (byWhat == 1)
    {
        if (!printEvents(events))
        {
            print(ERROR_FUNC, "无项目信息\n");
            return;
        }
        id = getValidNumInput("请输入查询的项目ID：", 1, events->size);
    }
    else
    {
        if (!printSchools(schools))
        {
            print(ERROR_FUNC, "无学校信息\n");
            return;
        }
        id = getValidNumInput("请输入查询的学校ID：", 1, schools->size);
    }
    if (byWhat == 1)
    {
        EventNode *eventNode = EventList_Get(events, id - 1);
        if (eventNode)
        {
            ResultNode *resultNode = eventNode->data.results->head;
            print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "获奖名单\n");
            print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "学校名称 成绩（得分）\n");
            print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "-------- --------\n");
            // 输出前三或前五的成绩
            for (int i = 0; i < MIN(scoreTypeToNum(eventNode->data.comType), eventNode->data.results->size); i++)
            {
                if (resultNode)
                {
                    printf("%-*s %s（%d）\n",
                           MAX_LENTH_NAME - 1,
                           resultNode->data.school.name,
                           resultToString(eventNode->data.comType, resultNode->data, '\0'),
                           resultToScore(eventNode->data, resultNode->data));
                    resultNode = resultNode->next;
                }
                else
                {
                    print(ERROR_FUNC, "未找到相关的成绩！\n");
                    return;
                }
            }
            // 是否继续输出剩余成绩
            if (eventNode->data.results->size > scoreTypeToNum(eventNode->data.comType))
            {
                if (getValidNumInput("输出剩余的成绩（1.是 0.否）：", 0, 1))
                {
                    ResultNode *resultNode = ResultList_Get(eventNode->data.results, scoreTypeToNum(eventNode->data.comType));
                    while (resultNode)
                    {
                        printf("%-*s %s（%d）\n",
                               MAX_LENTH_NAME - 1,
                               resultNode->data.school.name,
                               resultToString(eventNode->data.comType, resultNode->data, '\0'),
                               resultToScore(eventNode->data, resultNode->data));
                        resultNode = resultNode->next;
                    }
                }
            }
        }
    }
    else
    {
        EventList_Sort(events, event_CmpById);
        SchoolNode *schoolNode = SchoolList_Get(schools, id - 1);
        if (schoolNode)
        {
            print(getFunc(C_BOLD, F_BLUE, B_DEFAULT), "项目名称 成绩（得分）\n");
            print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "-------- --------\n");
            // 遍历所有项目，查找当前学校的成绩
            for (EventNode *eventNode = events->head; eventNode; eventNode = eventNode->next)
            {
                for (ResultNode *resultNode = eventNode->data.results->head; resultNode; resultNode = resultNode->next)
                {
                    if (!school_CmpById(&(resultNode->data.school), &(schoolNode->data)))
                    {
                        printf("%-*s %s（%d）\n",
                               MAX_LENTH_NAME - 1,
                               eventNode->data.name,
                               resultToString(eventNode->data.comType, resultNode->data, '\0'),
                               resultToScore(eventNode->data, resultNode->data));
                    }
                }
            }
        }
    }
    return;
}
