#ifndef _PREHEAD_H_
#define _PREHEAD_H_

// 最大姓名长度
#define MAX_LENTH_NAME 21
// 最大结果长度
#define MAX_LENTH_RESULT 13
// 最大文件路径长度
#define MAX_LENTH_FILEPATH 100
// 错误与成功定义
#define DNF 0
#define MEMORY_ERROR -1
#define SUCCESS 0
#define ERROR -1
#define FILEPATH "data.ini"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"
#include "print.h"

// 调试相关宏
#ifndef _DEBUG
#define MAX_SCHOOL 100
#define MAX_EVENT 200
#else
#define MAX_SCHOOL 20
#define MAX_EVENT 40
#endif
// 项目类型
typedef enum
{
    maleTrack = 1,   // 男子径赛
    maleField = 2,   // 男子田赛
    femaleTrack = 3, // 女子径赛
    femaleField = 4  // 女子田赛
} ComType;

// 性别
typedef enum
{
    male = 1,
    female = 2
} Sex;

// 计分类型
typedef enum
{
    topThree = 1,
    topFive = 2
} ScoreType;

extern Func LIST_FUNC;
extern Func ERROR_FUNC;
extern Func PROMPT_FUNC;
extern Func SUCCESS_FUNC;
// 得分数组
const static int ScoreFive[] = {7, 5, 3, 2, 1};
const static int ScoreThree[] = {5, 3, 2};
// 数据是否改变
extern bool isDataChange;
// 宏函数定义
#define memoryCheck(a) MEMORY_ERROR != a
#define getComType(type) ((type) == maleTrack ? "男子径赛" : type == maleField ? "男子田赛" \
                                                         : type == femaleTrack ? "女子径赛" \
                                                                               : "女子田赛")
#define getSex(type) ((type) ? "女" : "男")
#define getScoreType(type) ((type) == topThree ? "得分前三" : "得分前五")
#define scoreTypeToNum(type) ((type) == topThree ? 3 : 5)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int getValidNumInput(const char *prompt, int min, int max);

#endif