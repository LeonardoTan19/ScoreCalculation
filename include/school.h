#ifndef _SCHOOL_H
#define _SCHOOL_H
#include "prehead.h"
#include "list.h"

extern int nextSchoolId;
typedef struct school
{
    int id;
    char name[MAX_LENTH_NAME];
    int MaleScore;
    int FemaleScore;
} School;
List(School)
// 比较学校名字
int school_CmpById(const School *a, const School *b);
int school_CmpByMaleScore(const School *a, const School *b);
int school_CmpByFemaleScore(const School *a, const School *b);
int school_CmpByTotalScore(const School *a, const School *b);
// 创建学校
School createSchool(char* name);
// 打印学校
int printSchools(const SchoolList schools);
// 录入学校
void inputSchool(const SchoolList schools);
// 修改学校
void modifySchool(const SchoolList schools);

#endif