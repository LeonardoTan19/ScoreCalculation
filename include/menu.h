#ifndef _MENU_H_
#define _MENU_H_

#include "config.h"
#include "prehead.h"
#include "event.h"
#include "school.h"
#include "store.h"
#include "result.h"


// 函数指针类型，用于菜单回调
typedef void (*MenuPointer)();

// 根据调试或发布版本打印不同的欢迎信息
#ifdef _DEBUG
#define printWelcome() print(getFunc(C_BOLD, F_BLUE, B_DEFAULT), "**正在调试**\n")
#else
#define printWelcome() print(getFunc(C_BOLD, F_RED, B_DEFAULT), "**欢迎使用运动会分数统计系统**\n")
#endif

// 主菜单
MenuPointer mainMenu();

// 查询菜单
void queryMenu();
// 录入菜单
void inputMenu();
// 修改菜单
void modifyMenu();
// 保存菜单
void saveMenu();
// 退出菜单
void exitMenu();
#endif