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



/*********************************************************************************/
void MouseMoveTo(int x, int y);  // x,y坐标;

void MouseClick(int x, int y, int clicks, char button[]);  // 鼠标点击函数

void GetScreenSIze();  // 获取分辨率函数

void GetMousePosition();  // 获取光标目前所在的坐标

void PressHotKey(char *key1, char *key2, char *key3);  // 按下快捷键

void PressKey(char *key); // 按键

void WriteStr(char str_print[], int str_size); // 输入字符窜函数但仅可用英文







#endif