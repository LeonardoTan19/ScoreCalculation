#ifndef _RESULT_H_
#define _RESULT_H_
#include "school.h"
#include "list.h"
#include "prehead.h"

typedef struct Result
{
    School school;
    int grade;
} Result;
// 初始化成绩列表，提供接口
List(Result)
char* resultToString(ComType comType,Result result,char end);
int result_CmpByGrade_Track(const Result *a, const Result *b);
int result_CmpByGrade_Field(const Result *a, const Result *b);
Result createResult(School school,int grade);
int getResultRank(ResultList results, Result result);
int result_cmpBySchoolID(const Result *a,const Result *b);
int stringToResult(ComType comType,char *str);
#endif