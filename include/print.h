// Last update: 2025-2-11 BY 谭铭辉
#ifndef _PRINT_H_
#define _PRINT_H_

#define C_DEFAULT "0"      // 恢复
#define C_BOLD "1"         // 粗体
#define C_FAINT "2"        // 暗淡
#define C_UNDERLINE "4"    // 下划线
#define C_BLINK "5"        // 闪烁
#define C_REVERSE "7"      // 反转
#define C_HIDE "8"         // 隐藏
#define C_CLEAR "2J"       // 清除
#define C_CLRLINE "K"      // 清除行
#define C_CLEAR "2J"       // 清屏幕
#define C_HIDEMOUSE "?25l" // 隐藏光标
#define C_SHOWMOUSE "?25h" // 显示光标

#define F_RED "31"     // 红色
#define F_GREEN "32"   // 绿色
#define F_YELLOW "33"  // 黄色
#define F_BLUE "34"    // 蓝色
#define F_PURPLE "35"  // 紫色
#define F_CYAN "36"    // 青色
#define F_WHITE "37"   // 白色
#define F_DEFAULT "39" // 默认

#define B_BLACK "40"   // 黑色
#define B_RED "41"     // 红色
#define B_GREEN "42"   // 绿色
#define B_YELLOW "43"  // 黄色
#define B_BLUE "44"    // 蓝色
#define B_PURPLE "45"  // 紫色
#define B_CYAN "46"    // 青色
#define B_WHITE "47"   // 白色
#define B_DEFAULT "49" // 默认

#define NONE "\e[0m"  // 结束
#define SEMICOLON ";" // 分号
#define END "m"       // 结束

// 输出格式
typedef struct {
    char *control;
    char *front;
    char *back;
} Func;

// 彩色打印函数，接受格式化字符串及可变参数
int print(const Func func, const char *__format, ...);
// 设置输出格式
Func getFunc(char *control, char *front, char *back);

#endif
