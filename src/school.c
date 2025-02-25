#include "school.h"
#include <stdio.h>
int nextSchoolId = 1;
int school_CmpById(const School *a, const School *b)
{
    return a->id - b->id;
}
int school_CmpByName(const School *a, const School *b)
{
    return strcmp(a->name, b->name);
}
int school_CmpByMaleScore(const School *a, const School *b)
{
    return b->MaleScore - a->MaleScore;
}
int school_CmpByFemaleScore(const School *a, const School *b)
{
    return b->FemaleScore - a->FemaleScore;
}
int school_CmpByTotalScore(const School *a, const School *b)
{
    return b->MaleScore + b->FemaleScore - a->MaleScore - a->FemaleScore;
}

School createSchool(char *name)
{
    School school;
    school.id = nextSchoolId++;
    memset(school.name, 0, MAX_LENTH_NAME);
    strncat(school.name, name, MAX_LENTH_NAME - 1);
    school.MaleScore = 0;
    school.FemaleScore = 0;
    return school;
}
int printSchools(const SchoolList schools)
{
    if (schools && schools->head)
    {
        print(getFunc(C_BOLD, F_BLUE, B_DEFAULT), "学校信息\n");
        print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "编号  学校名称         男子团体得分 女子团体得分 总得分\n");
        print(getFunc(C_FAINT, F_BLUE, B_DEFAULT), "---- ---------------- ----------- ----------- -------\n");
        int i=1;
        for (SchoolNode *schoolNode = schools->head; schoolNode; schoolNode = schoolNode->next)
        {
            printf("%-4d %-*s %-13d %-13d %-13d\n", i++, MAX_LENTH_NAME - 1, schoolNode->data.name, schoolNode->data.MaleScore, schoolNode->data.FemaleScore, schoolNode->data.MaleScore + schoolNode->data.FemaleScore);
        }
    }
    else
    {
        print(getFunc(C_BOLD, F_RED, B_DEFAULT), "没有学校信息可显示\n");
    }
    return schools->size;
}
void inputSchool(const SchoolList schools)
{
    int count;
    count = getValidNumInput("请输入要录入的学校数量（0以取消）：", 0, MAX_SCHOOL - schools->size);
    getchar();
    for (int i = 0; i < count; i++)
    {
        print(getFunc(C_BOLD, F_BLUE, B_YELLOW), "【录入第%d个】", i + 1);
        print(PROMPT_FUNC, "请输入学校名称：");
        char name[MAX_LENTH_NAME];
        fgets(name, MAX_LENTH_NAME - 1, stdin);
        name[strlen(name) - 1] = '\0';
        SchoolList_Insert_Tail(schools, createSchool(name));
        print(PROMPT_FUNC, "学校录入成功！\n");
        isDataChange = true;
    }
}

void modifySchool(const SchoolList schools)
{
    if (printSchools(schools) == 0)
        return;
    int id = getValidNumInput("请输入要修改的学校编号（0以取消）：", 0, schools->size);
    if (id == 0)
        return;
    id--;
    SchoolNode *schoolNode = SchoolList_Get(schools, id);
    if (schoolNode)
    {
        print(PROMPT_FUNC, "请输入新的学校名称（输入#删除该学校）：");
        char name[MAX_LENTH_NAME];
        getchar();
        fgets(name, MAX_LENTH_NAME - 1, stdin);
        name[strlen(name) - 1] = '\0';
        if (strcmp(name, "#") == 0)
        {
            SchoolList_Delete(schools, id);
            print(PROMPT_FUNC, "学校删除成功！\n");
        }
        else
        {
            schoolNode->data = createSchool(name);
            print(PROMPT_FUNC, "学校修改成功！\n");
        }
        isDataChange = true;
    }
    else
    {
        print(getFunc(C_BOLD, F_RED, B_DEFAULT), "没有找到该学校！\n");
    }
}