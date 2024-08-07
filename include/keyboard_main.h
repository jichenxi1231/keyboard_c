#ifndef KEYBOARD_MAIN_H
#define KEYBOARD_MAIN_H
#include <windows.h>

typedef struct ScreenSize  // 声明结构体获取屏幕大小
{
    int x;
    int y;
} ScreenSizeGet;  // 定义标签
ScreenSizeGet get_scree_size = {0, 0};  // 分辨率初始化大小

/********************************************************/
typedef struct MousePosition  // 获取光标所在当前位置
{
    LONG x;
    LONG y;
}MousePositionGet;
MousePositionGet get_mouse_position = {0, 0};  // 初始化光标位置
/*********************** 呃 复制字符窜的结构体 *******************/
typedef struct copy_str_structs  // 字符窜剪切的结构体(防止后续重复利用相同字符窜)
{
    const char* textToCopy;  // 一个常量指针字符窜
    void (*copy_str_in)(struct copy_str_structs);  // 复制到剪切板的函数，后续包裹到CopyStr中
}copy_str_structs;

void copy_str_in(copy_str_structs self);  // 复制到剪切板的函数，后续包裹在CopyStr函数中



/*********************************************************************************/
void MouseMoveTo(int x, int y);  // x,y坐标;

void MouseClick(int x, int y, int clicks, char button[]);  // 鼠标点击函数

void GetScreenSIze();  // 获取分辨率函数

void GetMousePosition();  // 获取光标目前所在的坐标

void PressHotKey(char *key1, char *key2, char *key3);  // 按下快捷键

void PressKey(char *key); // 按键

void WriteStr(const char str_print[], int str_size); // 输入字符窜函数但仅可用英文

void CopyStr(const char *str);  // 复制字符窜到剪切板

void PasteStr(); // 获取剪切板数据(没用上)








#endif