#ifndef KEYBOARD_MAIN_H
#define KEYBOARD_MAIN_H
#include <windows.h>
#include <stdbool.h>
#define True 1
#define False 0

/************* press up flag **************/

typedef struct
{
    bool mouse_up;
    char *mouse_name
}MouseUps;
MouseUps flag_up = {true, ""};

typedef struct PressHotKeyNameUp
{
    int key_num;  // 按下的数量
    int key_code[108];
}PressHotKeyNameUp;  // 释放按下的按键
PressHotKeyNameUp free_keys = {0, 0}; // 释放按键

/******************************************/

typedef struct ScreenSize  // 声明结构体获取屏幕大小
{
    int x;
    int y;
} ScreenSizeGet;  // 定义标签

/************ 鼠标按下与释放 ************/
typedef struct
{
    char *button;
}MouseDownAndUp;  // 定义鼠标按下或者释放的结构体


/********************************************************/
typedef struct MousePosition  // 获取光标所在当前位置
{
    LONG x;
    LONG y;
}MousePositionGet;
/*********************** 呃 复制字符窜的结构体 *******************/
typedef struct copy_str_structs  // 字符窜剪切的结构体(防止后续重复利用相同字符窜)
{
    const char* textToCopy;  // 一个常量指针字符窜
    void (*copy_str_in)(struct copy_str_structs);  // 复制到剪切板的函数，后续包裹到CopyStr中
}copy_str_structs;

/***************** 注册快捷键 *********************/

// 定义一个结构体来存储快捷键信息
typedef struct HotKey
{
    char *key1;          // 第一个键名
    char *key2;          // 第二个键名
    char *key3;          // 第三个键名
    char *key4;          // 第四个键名
//    void (*function)(void);  // 被调用的函数指针
} AddHotKeyInput;  // 接受传入的参数(快捷键名称)

// 使用一个链表来存储多个快捷键
typedef struct HotKeyList
{
    AddHotKeyInput data;  // 快捷键数据, 存储一个 AddHotKeyInput 结构体实例，即快捷键的数据。
    struct HotKeyList *next;  // 指向下一条记录的指针，指向下一个 HotKeyList 结构体实例的指针，用于链接多个节点形成链表。
} HotKeyList;

// 定义一个函数指针类型
typedef void (*FunctionPtr)();

// 定义一个函数数组结构体
typedef struct
{
    /********** 四个快捷键数组大小 *********/
    int size_four_key_ctrl_alt_shift;
    int size_four_key_ctrl_shift_alt;
    int size_four_key_alt_ctrl_shift;
    int size_four_key_alt_shift_ctrl;
    int size_four_key_shift_ctrl_alt;
    int size_four_key_shift_alt_ctrl;
////////////////////////////////////////////
    int size_three_ctrl_alt;  // 三个快捷键
    int size_three_ctrl_shift;
    int size_three_alt_ctrl;
    int size_three_alt_shift;
    int size_three_shift_ctrl;
    int size_three_shift_alt;
///////////////////////////////////////////////
    int size_two_ctrl;  // 双快捷键
    int size_two_alt;
    int size_two_shift;

    int size_one;

    /**** 四个快捷键名字 ****/
    char *four_key_name_ctrl_alt_shift[53];
    char *four_key_name_ctrl_shift_alt[53];
    char *four_key_name_alt_ctrl_shift[53];
    char *four_key_name_alt_shift_ctrl[53];
    char *four_key_name_shift_ctrl_alt[53];
    char *four_key_name_shift_alt_ctrl[53];


///////////////////////////////////////////////////////
    char *three_key_name_ctrl_alt[53];  // 三快捷键
    char *three_key_name_ctrl_shift[53];
    char *three_key_name_alt_ctrl[53];
    char *three_key_name_alt_shift[53];
    char *three_key_name_shift_ctrl[53];
    char *three_key_name_shift_alt[53];

    char *tow_key_name_ctrl[53];  // 双快捷键
    char *tow_key_name_alt[53];
    char *tow_key_name_shift[53];

    char *one_key_name[53];

    FunctionPtr *funcArray_four_key_ctrl_alt_shift;
    FunctionPtr *funcArray_four_key_ctrl_shift_alt;
    FunctionPtr *funcArray_four_key_alt_ctrl_shift;
    FunctionPtr *funcArray_four_key_alt_shift_ctrl;
    FunctionPtr *funcArray_four_key_shift_ctrl_alt;
    FunctionPtr *funcArray_four_key_shift_alt_ctrl;

    // 三个快捷键
    FunctionPtr *funcArray_three_key_ctrl_alt;
    FunctionPtr *funcArray_three_key_ctrl_shift;
    FunctionPtr *funcArray_three_key_alt_ctrl;
    FunctionPtr *funcArray_three_key_alt_shift;
    FunctionPtr *funcArray_three_key_shift_ctrl;
    FunctionPtr *funcArray_three_key_shift_alt;

    FunctionPtr *funcArray_two_key_ctrl;  // 双快捷键
    FunctionPtr *funcArray_two_key_alt;
    FunctionPtr *funcArray_two_key_shift;

    FunctionPtr *funcArray_one_key;

}Func_List;  // 配合快捷键注册与判断


/********* 获取剪切板内容 *********/
typedef struct {
    char* text; // 指向剪贴板文本的指针
    size_t length; // 文本长度
}PasteStrStructs;



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);  // 快捷键回调函数

void freeHotKeys();  // 释放结构体内存函数


/********************************************/

void copy_str_in(copy_str_structs self);  // 复制到剪切板的函数，后续包裹在CopyStr函数中



/***************************** 主功能区 **************************************************/
void MouseMoveTo(int x, int y);  // x,y坐标;

void MouseDown(char *button);  // 鼠标按下键位

void MouseUp(char *button);  // 鼠标释放

void MouseClick(int x, int y, int clicks, char button[]);  // 鼠标点击函数

//void GetScreenSIze();  // 获取分辨率函数(弃用)

//void GetMousePosition();  // 获取光标目前所在的坐标(弃用)

void MouseRoll(int move);  // 鼠标滚轮,正数向上负数向下

void KeyDown(char *key);  // 键盘按下

void KeyUp(char *key);  // 键盘释放

void PressHotKey(char *key1, char *key2, char *key3);  // 按下快捷键

void PressKey(char *key); // 按键

void WriteStr(const char str_print[], int str_size); // 输入字符窜函数但仅可用英文

void CopyStr(const char *str);  // 复制字符窜到剪切板

void FreePasteStr(PasteStrStructs * clipboardText); // 传参主函数实例化的结构体，释放获取剪贴板内容时分配的内存(暂存)

void AddHotKey(char *key1, char *key2, char *key3, char *key4, void (*target_void_func)());  // 添加快捷键的函数不输入的传NULL

void ClearHotKey(); // 注销快捷键(自动注销快捷键调用释放内存的函数)

void ListenHotKEy();  // 监听快捷键

void ExitCheckWork();  // 突然结束检查


/************* 获取坐标的函数 ***************/
ScreenSizeGet GetScreenSIze(bool out_put);  // 获取分辨率函数，布偶值选择是否输出坐标

MousePositionGet GetMousePosition(bool out_put);  // 获取光标目前所在的坐标，鼠标坐标，布偶值选择是否输出坐标

PasteStrStructs PasteStr();  // 存储返回的字符窜内容


/*************** 单个按键监听判断函数 (适合游戏) ****************/
bool KeyUpListen(char *key);  // 监听键盘抬起
bool KeyDownListen(char *key); // 监听键盘按下


/******************** 尾部清理 ******************/
void cleanup_check();  // 执行清理任务的函数
void handle_sigint(int sig);  // 检查是否被接受的终止信号
void free_funcs();  // 释放函数内存



#endif