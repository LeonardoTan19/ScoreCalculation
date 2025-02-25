#include "result.h"
#include "stdio.h"
char *resultToString(ComType comType, Result result, char end)
{
    char *str = (char *)calloc(MAX_LENTH_RESULT + 5, sizeof(char));
    // 判断比赛类型
    if (comType % 2)
    {
        int hour = result.grade / 1000000,
            minute = result.grade / 10000 % 100,
            second = result.grade / 100 % 100,
            centisecond = result.grade % 100;
        if (hour)
            snprintf(str, MAX_LENTH_RESULT + MAX_LENTH_NAME + 5, "%02dh%02d'%02d\"%02d%c",
                     hour, minute, second, centisecond, end);
        else if (minute)
            snprintf(str, MAX_LENTH_RESULT + MAX_LENTH_NAME + 5, "%02d'%02d\"%02d%c",
                     minute, second, centisecond, end);
        else
            snprintf(str, MAX_LENTH_RESULT + MAX_LENTH_NAME + 5, "%02d\"%02d%c",
                     second, centisecond, end);
    }
    else
    {
        snprintf(str, MAX_LENTH_RESULT, "%.2fm%c", (float)result.grade / 100, end);
    }
    return str;
}
int result_CmpByGrade_Track(const Result *a, const Result *b)
{
    return (a->grade - b->grade) ? a->grade - b->grade : (a->school.id - b->school.id);
}
int result_CmpByGrade_Field(const Result *a, const Result *b)
{
    return (b->grade - a->grade) ? b->grade - a->grade : (a->school.id - b->school.id);
}
int result_Equal(const Result *a, const Result *b)
{
    return !(a->grade == b->grade && a->school.id == b->school.id);
}
Result createResult(School school, int grade)
{
    Result result;
    result.school = school;
    result.grade = grade;
    return result;
}
int getResultRank(ResultList results, Result result)
{
    return ResultList_Find(results, result, result_Equal);
}
int result_cmpBySchoolID(const Result *a, const Result *b)
{
    return a->school.id - b->school.id;
}
int stringToResult(ComType comType, char *str)
{
    int hour, minute, second, centisecond;
    int grade;
    if (strcmp(str, "DNF") == 0)
    {
        return DNF;
    }
    if (comType % 2)
    {
        if (sscanf(str, "%dh%02d'%02d\"%02d", &hour, &minute, &second, &centisecond) == 4)
            grade = hour * 1000000 + minute * 10000 + second * 100 + centisecond;
        else if (sscanf(str, "%02d'%02d\"%02d", &minute, &second, &centisecond) == 3)
            grade = minute * 10000 + second * 100 + centisecond;
        else if (sscanf(str, "%02d\"%02d", &second, &centisecond) == 2)
            grade = second * 100 + centisecond;
        else
            grade = ERROR;
    }
    else
    {
        float temp;
        if (sscanf(str, "%fm", &temp) == 1)
            grade = (int)(temp * 100);
        else
            grade = ERROR;
    }
    return grade;
}
