#include "menu.h"
#include "stdio.h"

typedef struct
{
    char *name;       // 菜单选项名称
    MenuPointer menu; // 对应的菜单函数指针
} Option;

// 定义主菜单的各个选项
Option options[] = {
    {"信息查询菜单", queryMenu},
    {"信息录入菜单", inputMenu},
    {"信息修改菜单", modifyMenu},
    {"信息保存", saveMenu},
    {"退出", exitMenu}};

// listFunc 用于指定字体样式等参数
void printMainMenuOptions(Func listFunc)
{
    print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "■功能列表■\n");
    for (int i = 0; i < sizeof(options) / sizeof(Option); i++)
    {
        print(LIST_FUNC, "%d. %s\n", i + 1, options[i].name);
    }
}

MenuPointer mainMenu()
{
    printMainMenuOptions(LIST_FUNC);
    int option = getValidNumInput("请输入功能编号：", 1, sizeof(options) / sizeof(Option));
    return options[option - 1].menu;
}

void queryMenu()
{
    print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "★查询菜单★\n");
    print(LIST_FUNC, "0. 重新打印菜单\n");
    print(LIST_FUNC, "1. 查询项目信息\n");
    print(LIST_FUNC, "2. 查询学校信息\n");
    print(LIST_FUNC, "3. 查询比赛结果\n");
    print(LIST_FUNC, "4. 返回主菜单\n");

    while (1)
    {
        int option = getValidNumInput("请输入功能编号：", 0, 4);
        switch (option)
        {
        case 0:
            print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "★查询菜单★\n");
            print(LIST_FUNC, "0. 重新打印菜单\n");
            print(LIST_FUNC, "1. 查询项目信息\n");
            print(LIST_FUNC, "2. 查询学校信息\n");
            print(LIST_FUNC, "3. 查询比赛结果\n");
            print(LIST_FUNC, "4. 返回主菜单\n");
            break;
        case 1:
            printEvents(events);
            break;
        case 2:
            print(getFunc(C_DEFAULT, F_YELLOW, B_DEFAULT),
                  "1.按编号排序\n2.按男子团体得分排序\n3.按女子团体得分排序\n4.按总得分排序\n");
            {
                int sortMethod = getValidNumInput("请选择排序方式：", 1, 5);
                int (*cmp[])(const School *, const School *) = {
                    school_CmpById,
                    school_CmpByMaleScore,
                    school_CmpByFemaleScore,
                    school_CmpByTotalScore};
                SchoolList temp = SchoolList_Copy_Shallow(schools);
                SchoolList_Sort(temp, cmp[sortMethod - 1]);
                printSchools(temp);
                SchoolList_Destroy(temp);
            }
            break;
        case 3:
            printEventResult(events);
            break;
        case 4:
            return;
        }
    }
}

void inputMenu()
{
    print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "★录入菜单★\n");
    print(LIST_FUNC, "0. 重新打印菜单\n");
    print(LIST_FUNC, "1. 录入项目信息\n");
    print(LIST_FUNC, "2. 录入学校信息\n");
    print(LIST_FUNC, "3. 录入比赛结果\n");
    print(LIST_FUNC, "4. 返回主菜单\n");

    while (1)
    {
        int option = getValidNumInput("请输入功能编号：", 0, 4);
        switch (option)
        {
        case 0:
            print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "★录入菜单★\n");
            print(LIST_FUNC, "0. 重新打印菜单\n");
            print(LIST_FUNC, "1. 录入项目信息\n");
            print(LIST_FUNC, "2. 录入学校信息\n");
            print(LIST_FUNC, "3. 录入比赛结果\n");
            print(LIST_FUNC, "4. 返回主菜单\n");
            break;
        case 1:
            inputEvent(events);
            break;
        case 2:
            inputSchool(schools);
            break;
        case 3:
            inputResult(events);
            calculateScore(events, schools);
            break;
        case 4:
            return;
        }
    }
}

void modifyMenu()
{
    print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "★修改菜单★\n");
    print(LIST_FUNC, "0. 重新打印菜单\n");
    print(LIST_FUNC, "1. 修改项目信息\n");
    print(LIST_FUNC, "2. 修改学校信息\n");
    print(LIST_FUNC, "3. 修改比赛结果\n");
    print(LIST_FUNC, "4. 返回主菜单\n");

    while (1)
    {
        int option = getValidNumInput("请输入功能编号：", 0, 4);
        switch (option)
        {
        case 0:
            print(getFunc(C_BOLD, F_YELLOW, B_DEFAULT), "★修改菜单★\n");
            print(LIST_FUNC, "0. 重新打印菜单\n");
            print(LIST_FUNC, "1. 修改项目信息\n");
            print(LIST_FUNC, "2. 修改学校信息\n");
            print(LIST_FUNC, "3. 修改比赛结果\n");
            print(LIST_FUNC, "4. 返回主菜单\n");
            break;
        case 1:
            modifyEvent(events);
            break;
        case 2:
            modifySchool(schools);
            break;
        case 3:
            // 修改比赛结果并重新计算得分
            modifyResult(events);
            calculateScore(events, schools);
            break;
        case 4:
            return;
        }
    }
}

void saveMenu()
{
    // 调用保存函数，如果返回SUCCESS则表示保存成功
    if (SUCCESS == fullSave(events, schools))
    {
        print(SUCCESS_FUNC, "数据保存成功\n");
        isDataChange = false; // 更新数据状态
    }
    else
        print(ERROR_FUNC, "数据保存失败！\n");
}

void exitMenu()
{
    print(SUCCESS_FUNC, "欢迎使用本系统，再见！\n");

    // 如果数据有改动，则询问用户是否保存
    if (isDataChange)
    {
        int choice = getValidNumInput("当前有未保存的数据，是否保存？(0.不保存 1.保存 2.取消)：", 0, 2);
        if (choice == 1)
            saveMenu();
        else if (choice == 2)
            return;
    }
    exit(0); // 退出程序
}