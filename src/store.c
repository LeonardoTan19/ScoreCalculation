#include "store.h"
#include "event.h"
#include "school.h"
#include <sys/stat.h>
struct stat file_stat;
int fullSave(EventList events, SchoolList schools)
{

    FILE *file = fopen(FILEPATH, "w");
    if (file == NULL || stat(FILEPATH, &file_stat) != 0)
    {
        perror("打开文件失败");
        return ERROR;
    }
    fprintf(file,"校验数据，修改后数据将不可用：");
    fprintf(file, "%ld\n",file_stat.st_mtime);
    fprintf(file, "SCHOOLS:%d\n", schools->size);
    for (SchoolNode *schoolNode = schools->head; schoolNode != NULL; schoolNode = schoolNode->next)
    {
        School school = schoolNode->data;
        fprintf(file, "{%d,%s,%d,%d}\n", school.id, school.name, school.MaleScore, school.FemaleScore);
    }
    fprintf(file, "EVENTS:%d\n", events->size);
    for (EventNode *eventNode = events->head; eventNode != NULL; eventNode = eventNode->next)
    {
        Event event = eventNode->data;
        fprintf(file, "{%d,%s,%d,%d", event.id, event.name, event.comType, event.scoreType);
        if (event.results != NULL)
        {
            fprintf(file, ",[");
            for (ResultNode *resultNode = event.results->head; resultNode != NULL; resultNode = resultNode->next)
            {
                fprintf(file, "%d,%d", resultNode->data.school.id, resultNode->data.grade);
                if (resultNode->next != NULL)
                {
                    fprintf(file, ",");
                }
            }
            fprintf(file, "]");
        }
        fprintf(file, "}\n");
    }
    stat(FILEPATH, &file_stat);
    fclose(file);
    return SUCCESS;
}
int fullLoad(EventList events, SchoolList schools)
{
    isDataChange = false;
    FILE *file = fopen(FILEPATH, "r");
    if (file == NULL || stat(FILEPATH, &file_stat) != 0)
    {
        perror("打开文件失败");
        return ERROR;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "校验数据，修改后数据将不可用：", 45) == 0)
        {
            long lastTime;
            sscanf(line, "校验数据，修改后数据将不可用：%ld", &lastTime);
            if (file_stat.st_mtime - lastTime > 2)
            {
                printf("文件已被修改，数据未被导入\n");
                return ERROR;
            }
        }
        else if (strncmp(line, "SCHOOLS:", 8) == 0)
        {
            int size;
            sscanf(line, "SCHOOLS:%d", &size);
            for (int i = 0; i < size; i++)
            {
                School school;
                fscanf(file, "{%d,%[^,],%d,%d}\n", &school.id, school.name, &school.MaleScore, &school.FemaleScore);
                nextSchoolId++;
                SchoolList_Insert_Tail(schools, school);
            }
        }
        else if (strncmp(line, "EVENTS:", 7) == 0)
        {
            int size;
            sscanf(line, "EVENTS:%d", &size);
            for (int i = 0; i < size; i++)
            {
                Event event;
                fscanf(file, "{%d,%[^,],%d,%d", &event.id, event.name, &event.comType, &event.scoreType);
                event.results = NULL;
                nextEventId++;
                char c;
                fscanf(file, "%c", &c);
                if (c == ',')
                {
                    event.results = ResultList_Init();
                    fscanf(file, "[");
                    while (1)
                    {
                        Result result;
                        int schoolId;
                        fscanf(file, "%d,%d", &schoolId, &result.grade);
                        result.school = SchoolList_Get(schools, schoolId-1)->data;
                        ResultList_Insert_Tail(event.results, result);
                        if (fgetc(file) == ']')
                        {
                            break;
                        }
                    }
                }
                fscanf(file, "}\n");
                EventList_Insert_Tail(events, event);
            }
        }
    }
    fclose(file);
    return SUCCESS;
}

int calculateScore(EventList events, SchoolList schools)
{
    for(int i = 0; i < events->size; i++)
    {
        EventNode *eventNode = EventList_Get(events, i);
        if (eventNode)
        {
            ResultList_Sort(eventNode->data.results, eventNode->data.comType % 2 ? result_CmpByGrade_Track : result_CmpByGrade_Field);
        }
    }
    for (int i = 0; i < schools->size; i++) {
        SchoolNode *sNode = SchoolList_Get(schools, i);
        sNode->data.MaleScore = 0;
        sNode->data.FemaleScore = 0;
    }
    for (int i = 0; i < events->size; i++) {
        EventNode *eNode = EventList_Get(events, i);
        if (!eNode || !eNode->data.results) continue;
        for (ResultNode *rNode = eNode->data.results->head; rNode; rNode = rNode->next) {
            int score = resultToScore(eNode->data, rNode->data);
            SchoolNode *sn = SchoolList_Get(schools, rNode->data.school.id - 1);
            if (eNode->data.comType == maleTrack || eNode->data.comType == maleField) {
                sn->data.MaleScore += score;
            } else {
                sn->data.FemaleScore += score;
            }
        }
    }
    return SUCCESS;
}