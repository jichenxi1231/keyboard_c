#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "keyboard_main.h"
#include <unistd.h> // For sleep()
#include <signal.h> // For signal()



/*********** 虚键码对照表 Virtual key code mapping table **************/
const char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                               "h", "i", "j", "k", "l", "m",
                               "n", "o", "p", "q", "r", "s",
                               "t", "u", "v", "w", "x", "y", "z"  // 26字母
        ,"0", "1", "2", "3", "4", "5", "6"
        , "7", "8", "9"};  // 按键列  // 字母列表


const char *function_keys_list [] = {"ctrl", "alt", "shift", "F1", "F2", "F3", "F4", "F5",
                                     "F6", "F7", "F8", "F9", "F10", "F11", "F12", "esc",
                                     "space", "delete", "tab", "enter", "caps", "clear",
                                     "backspace", "win", "Pause", "page up", "page down", "left arrow",
                                     "right arrow", "down arrow", "up arrow", "insert"};



/****************************虚键码列表********************************/
int alphabet_code[] = {65, 66, 67, 68, 69, 70,
                       71, 72, 73, 74, 75, 76,
                       77, 78, 79, 80, 81, 82,
                       83, 84, 85, 86, 87, 88,
                       89, 90, 48, 49, 50, 51,  // 48 以后是数组
                       52, 53, 54, 55, 56, 57};  // 虚拟键码

int function_code[] = {VK_CONTROL, VK_MENU, VK_SHIFT, VK_F1, VK_F2, VK_F3,
                       VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
                       VK_F11, VK_F12, VK_ESCAPE, VK_SPACE, VK_DELETE, VK_TAB,
                       VK_RETURN, VK_CAPITAL, VK_CLEAR, VK_BACK, VK_LWIN, VK_PAUSE,
                       VK_PRIOR, VK_NEXT, VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_INSERT
};

/**************** 功能区 *******************/



void MouseMoveTo(int x, int y)
{
    SetCursorPos(x, y);  // 移动鼠标到某处(设置光标位置)
}

void MouseDown(const char *button)
{
    if (strcmp(button, "left") ==0)
    {
        // 如果没传参数默认左键
        INPUT input = {0};  // 定义INPUT结构体变量表示输入事件信息
        input.type = INPUT_MOUSE;  // 指定输入事件类型为鼠标事件
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;  // 设定鼠标事件为左键按下
        SendInput(1, &input, sizeof(INPUT));  // 使用SendInput函数发送鼠标事件
        // 设置鼠标被按下
    }
    else if (strcmp(button, "right") ==0)
    {
        // 如果没传参数默认左键
        INPUT input = {0};  // 定义INPUT结构体变量表示输入事件信息
        input.type = INPUT_MOUSE;  // 指定输入事件类型为鼠标事件
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;  // 设定鼠标事件为左键按下
        SendInput(1, &input, sizeof(INPUT));  // 使用SendInput函数发送鼠标事件
        // 设置鼠标被按下
    }
}

void MouseUp(const char *button)
{
    if  (strcmp(button, "left") ==0)
    {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // 假设是左键，根据需要调整
        SendInput(1, &input, sizeof(INPUT));
    }
    else if (strcmp(button, "right")==0)
    {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; // 假设是左键，根据需要调整
        SendInput(1, &input, sizeof(INPUT));}
}

/*********************************************************************************/

void MouseClick(int x, int y, int clicks, char button[])
{
    /* 当click为1时并且button不为None时执行单击一次的指令 */
    SetCursorPos(x, y);  // 移动鼠标到某处(设置光标位置)
    if (clicks!=0)
    {
        int click_time = 0;  // 初始化点击次数
        while (click_time <clicks && strcmp(button, "left") ==0)  // 当初始点击次数小于目标点击次数增
        {
            // 如果没传参数默认左键
            INPUT input = {0};  // 定义INPUT结构体变量表示输入事件信息
            input.type = INPUT_MOUSE;  // 指定输入事件类型为鼠标事件
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;  // 设定鼠标事件为左键按下
            SendInput(1, &input, sizeof(INPUT));  // 使用SendInput函数发送鼠标事件

            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;  // 设定鼠标事件为左键释放
            SendInput(1, &input, sizeof(INPUT));  // 发送释放鼠标左键事件
            click_time++;
        }

        while (click_time <clicks && strcmp(button, "right") ==0)  // 当初始点击次数小于目标点击次数增加
        {
            INPUT input = {0};  // 定义INPUT结构体变量表示输入事件信息
            input.type = INPUT_MOUSE;  // 指定输入事件类型为鼠标事件
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;  // 设定鼠标事件为左键按下
            SendInput(1, &input, sizeof(INPUT));  // 使用SendInput函数发送鼠标事件


            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;  // 设定鼠标事件为右键释放
            SendInput(1, &input, sizeof(INPUT));  // 发送释放鼠标右键事件
            click_time++;  // 初始值增加
        }
    }
}

ScreenSizeGet GetScreenSIze(bool out_put)
{
    ScreenSizeGet screen_size;
    int x_len, y_len;
    x_len=GetSystemMetrics(SM_CXSCREEN);  // 获取x长度
    y_len=GetSystemMetrics(SM_CYSCREEN);  // 获取y长度
    screen_size.x = x_len;  // 结构体储存大小(屏幕)
    screen_size.y = y_len;  // 结构体储存大小(屏幕)
    if (out_put) {
        printf("Display size x:%d, y:%d\n", screen_size.x, screen_size.y);
    }
    return screen_size;
//    If you want to get coordinates you need to instantiate the struct function:
//    ScreenSizeGet screen_size = GetScreenSIze; screen_size.x, screen_size.y
}
/**************************************************************/
MousePositionGet GetMousePosition(bool out_put)  // 获取光标目前所在的坐标
{
    POINT cursorPos;  // 实例化光标结构体，获取位置
    if (GetCursorPos(&cursorPos))
    {
        MousePositionGet mouse_position;  // 实力结构体取其中变量
        if (out_put) {
            printf("The current position of the cursor is x:%ld, y:%ld\n", cursorPos.x, cursorPos.y);
        }
        mouse_position.x = cursorPos.x;
        mouse_position.y = cursorPos.y;
        return mouse_position;  // 返回这个实例化的坐标，如果想要拿到坐标需要实例化
        // 获取坐标需要实力化结构体如和将函数的值复制在结构体实例的变量中当做参数传给结构体再获取
//        If you want to get coordinates you need to instantiate the struct function:
//        MousePositionGet mouse_position = GetMousePosition(); mouse_position.x,mouse_position.y
    }
    else
    {
        printf("Sorry, cursor coordinates not found\n");
    }

}

// 鼠标滚轮滚动
void MouseRoll(int move)
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;       // x坐标
    input.mi.dy = 0;       // y坐标
    input.mi.mouseData = move; // 滚动方向和距离
    input.mi.dwFlags = MOUSEEVENTF_WHEEL; // 发送滚轮事件
    input.mi.time = 0;     // 当前系统时间
    input.mi.dwExtraInfo = 0; // 额外信息

    SendInput(1, &input, sizeof(INPUT));
}


/*************** 键盘按下 ****************/
void key_down_record(int key_code)  // 记录键盘按下 (避免重复)
{
    int len = sizeof(free_keys.key_code) / sizeof(free_keys.key_code[0]);  // 检查按键数组大小
    bool found = false;  // 标记是否找到按键码

    // 遍历数组，检查按键码是否已经存在
    for (int i = 0; i < len; i++)
    {
        if (free_keys.key_code[i] == key_code)
        {
            found = true;  // 找到按键码，设置标记为true
            break;
        }
    }

    // 如果没有找到按键码，添加到数组的第一个空位置
    if (!found)  // 如果没找到 就重新遍历数组 寻找值为0的位置 将虚键码赋值在上面
    {
        for (int i = 0; i < len; i++)
        {
            if (free_keys.key_code[i] == 0)  // 找到数组的第一个空位置 (找到数组为0的位置，将虚键码赋值到上面)
            {
                free_keys.key_code[i] = key_code;
                break;
            }
        }
    }
}
void key_up_record(int key_code)  // 记录键盘松开，清空按键
{
    int len = sizeof(free_keys.key_code) / sizeof(free_keys.key_code[0]);  // 检查释放键盘的数组大小
    for (int i = 0; i < len; i++)
    {
        if (free_keys.key_code[i] == key_code)
        {
            free_keys.key_code[i] = 0;  // 清空按键码
            break;
        }
    }
}


void KeyDown(const char *key)
{
/****************列表长度************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // 字母数字长度
    int function_keys_list_len = sizeof (function_keys_list)/sizeof (function_keys_list[0]);  // 功能键数组长度


    for (int i = 0; i<alphabet_list_len; i++)
    {
        // 检查数组的字符是否与传入的参数一样(判断字母) 如果都没进入下一个循环
        if (strcmp(key, alphabet_list[i])==0)
        {
            INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

            input.type = INPUT_KEYBOARD; // 指定 input 的类型为键盘输入
            input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
            input.ki.time = 0; // 时间戳置为 0
            input.ki.dwExtraInfo = 0; // 额外信息置为 0

            // 模拟按下目标键
            input.ki.wVk = alphabet_code[i]; // 指定模拟按下的键为 目标 键
            input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
            SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统

            key_down_record(alphabet_code[i]);
            break;
        }
    }

    for (int i=0; i<function_keys_list_len; i++)
    {
        // 是否与传入的参数一样 (判断功能键)
        if (strcmp(key, function_keys_list[i])==0)
        {
            INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

            input.type = INPUT_KEYBOARD; // 指定 input 的类型为键盘输入
            input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
            input.ki.time = 0; // 时间戳置为 0
            input.ki.dwExtraInfo = 0; // 额外信息置为 0

            // 模拟按下目标键
            input.ki.wVk = function_code[i]; // 指定模拟按下的键为 目标 键
            input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
            SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统

            key_down_record(function_code[i]);
            break;
        }
    }
}

//////// 键盘释放 //////////
void KeyUp(const char *key)
{
    int len = sizeof (free_keys.key_code)/sizeof (free_keys.key_code[0]);
/****************列表长度************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // 字母数字长度
    int function_keys_list_len = sizeof (function_keys_list)/sizeof (function_keys_list[0]);  // 功能键数组长度

    for (int i = 0; i<alphabet_list_len; i++) {
        // 检查数组的字符是否与传入的参数一样(判断字母) 如果都没进入下一个循环
        if (strcmp(key, alphabet_list[i]) == 0) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = alphabet_code[i];  // 键位吗码
            // 如果之前按键被按下了，现在需要释放
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));

            key_up_record(alphabet_code[i]);
            break;
        }
    }


    for (int i=0; i<function_keys_list_len; i++)
    {
        // 是否与传入的参数一样 (判断功能键)
        if (strcmp(key, function_keys_list[i])==0)
        {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = function_code[i];  // 键位吗码
            // 如果之前按键被按下了，现在需要释放
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));

            key_up_record(function_code[i]);
            break;
        }
    }

//    INPUT input = {0};
//    input.type = INPUT_KEYBOARD;
//    input.ki.wVk = vkCode;  // 键位吗码
//    // 如果之前按键被按下了，现在需要释放
//    input.ki.dwFlags = KEYEVENTF_KEYUP;
//    SendInput(1, &input, sizeof(INPUT));
}

void PressHotKey(const char *key1, const char *key2, const char *key3)
{
    // 如果不使用其他快捷键输入None
    // 这里是查看两个数组，如果参数传入的与数组匹配就索引数组获得按键名称以及索引码


    const char *button_list[] = {"a", "b", "c", "d", "e", "f", "g",
                                 "h", "i", "j", "k", "l", "m",
                                 "n", "o", "p", "q", "r", "s",
                                 "t", "u", "v", "w", "x", "y", "z"  // 26字母
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // 按键列


    int button_code_list[] = {65, 66, 67, 68, 69, 70,
                              71, 72, 73, 74, 75, 76,
                              77, 78, 79, 80, 81, 82,
                              83, 84, 85, 86, 87, 88,
                              89, 90, 48, 49, 50, 51,
                              52, 53, 54, 55, 56, 57};  // 虚拟键码

    int len = sizeof (button_list)/sizeof (button_list[0]);  // 数组大小


    if (key1 != NULL && key2 != NULL)  // 检查两个字符窜是否为None
    {
        if (strcmp(key1, "ctrl") ==0) // 如果快捷键以ctrl开头
        {
            for (int i=0; i <len; i++)  // 匹配按键列表中与传入参数相同的按键并获取按键虚拟码
            {
                // 如果第二个键与参数相符
                if (strcmp(button_list[i], key2) ==0)
                {
                    // 创建一个输入结构体并初始化
                    INPUT inputs[2] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                    // 第一个按键 'ctrl' 的输入结构体
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'键的虚拟键码
                    inputs[0].ki.dwFlags = 0; // 表示按下按键

                    // 第二个按键 '传入的字符' 的输入结构体
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                    inputs[1].ki.dwFlags = 0; // 表示按下按键
                    // 发送输入，同时按下'ctrl'和'指定参数'键
                    SendInput(2, inputs, sizeof(INPUT));


                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));
                    break;  // break防止循环中多次点击快捷键
                }

                    // 如果第二个键是alt，， 以ctrl开头
                else if (strcmp(key2, "alt") ==0)
                {
                    if (key3!=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // 创建一个输入结构体并初始化
                        INPUT inputs[3] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'键的虚拟键码
                        inputs[0].ki.dwFlags = 0; // 表示按下按键

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_MENU; // 'alt'键的虚拟键码
                        inputs[1].ki.dwFlags = 0; // 表示按下按键

                        // 第二个按键 '传入的字符' 的输入结构体
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                        inputs[2].ki.dwFlags = 0; // 表示按下按键
                        // 发送输入，同时按下'ctrl，"alt',和'指定参数'键
                        SendInput(3, inputs, sizeof(INPUT));  // 按下

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        break;
                    }

                }

                    // 如果第二个参数为shift， ，以ctrl开头
                else if (strcmp(key2, "shift") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // 创建一个输入结构体并初始化
                        INPUT inputs[3] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'键的虚拟键码
                        inputs[0].ki.dwFlags = 0; // 表示按下按键

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
                        inputs[1].ki.dwFlags = 0; // 表示按下按键

                        // 第二个按键 '传入的字符' 的输入结构体
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                        inputs[2].ki.dwFlags = 0; // 表示按下按键
                        // 发送输入，同时按下'ctrl，"shift',和'指定参数'键
                        SendInput(3, inputs, sizeof(INPUT));  // 按下

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        break;
                    }

                }
            }
        }


            // 判断alt开头
        else if (strcmp(key1, "alt") ==0) // 如果快捷键以alt开头
        {
            for (int i=0; i <len; i++)  // 匹配按键列表中与传入参数相同的按键并获取按键虚拟码
            {
                if (strcmp(button_list[i], key2) ==0)
                {
                    // 创建一个输入结构体并初始化
                    INPUT inputs[2] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                    // 第一个按键 'alt' 的输入结构体
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_MENU; // 'alt'键的虚拟键码
                    inputs[0].ki.dwFlags = 0; // 表示按下按键

                    // 第二个按键 '传入的字符' 的输入结构体
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // '传入参数'键的虚拟键码
                    inputs[1].ki.dwFlags = 0; // 表示按下按键
                    // 发送输入，同时按下'ctrl'和'指定参数'键
                    SendInput(2, inputs, sizeof(INPUT));


                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));

                    break;
                }

                    // 如果第二个参数为ctrl，， 以alt开头
                else if(strcmp(key2, "ctrl") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // 创建一个输入结构体并初始化
                        INPUT inputs[3] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'键的虚拟键码
                        inputs[0].ki.dwFlags = 0; // 表示按下按键

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_MENU; // 'alt'键的虚拟键码
                        inputs[1].ki.dwFlags = 0; // 表示按下按键

                        // 第二个按键 '传入的字符' 的输入结构体
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                        inputs[2].ki.dwFlags = 0; // 表示按下按键
                        // 发送输入，同时按下'ctrl，"alt',和'指定参数'键
                        SendInput(3, inputs, sizeof(INPUT));  // 按下

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        break;
                    }

                }

                    // 如果第二个参数是shift,,以alt开头
                else if (strcmp(key2, "shift") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // 创建一个输入结构体并初始化
                        INPUT inputs[3] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_MENU; // 'alt'键的虚拟键码
                        inputs[0].ki.dwFlags = 0; // 表示按下按键

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
                        inputs[1].ki.dwFlags = 0; // 表示按下按键

                        // 第二个按键 '传入的字符' 的输入结构体
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                        inputs[2].ki.dwFlags = 0; // 表示按下按键
                        // 发送输入，同时按下'alt'，"shift',和'指定参数'键
                        SendInput(3, inputs, sizeof(INPUT));  // 按下

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        break;
                    }
                }
            }
        }


            // 判断shift开头
        else if (strcmp(key1, "shift") ==0) // 如果快捷键以shift开头
        {
            for (int i=0; i <len; i++)  // 匹配按键列表中与传入参数相同的按键并获取按键虚拟码
            {
                if (strcmp(button_list[i], key2) ==0)
                {
                    // 创建一个输入结构体并初始化
                    INPUT inputs[2] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                    // 第一个按键 'shift' 的输入结构体
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
                    inputs[0].ki.dwFlags = 0; // 表示按下按键

                    // 第二个按键 '传入的字符' 的输入结构体
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // 'B'键的虚拟键码
                    inputs[1].ki.dwFlags = 0; // 表示按下按键

                    // 发送输入，同时按下'shift'和'指定参数'键
                    SendInput(2, inputs, sizeof(INPUT));

                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));
                    break;
                }

                    // 如果第二个参数为ctrl.，，，shift开头
                else if (strcmp(key2, "ctrl") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // 创建一个输入结构体并初始化
                        INPUT inputs[3] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'键的虚拟键码
                        inputs[0].ki.dwFlags = 0; // 表示按下按键

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
                        inputs[1].ki.dwFlags = 0; // 表示按下按键

                        // 第二个按键 '传入的字符' 的输入结构体
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                        inputs[2].ki.dwFlags = 0; // 表示按下按键
                        // 发送输入，同时按下'ctrl，"alt',和'指定参数'键
                        SendInput(3, inputs, sizeof(INPUT));  // 按下
                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        break;
                    }
                }

                    // 判断第二个参数是否是alt,,,以shift开头
                else if(strcmp(key2, "alt") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // 创建一个输入结构体并初始化
                        INPUT inputs[3] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_MENU; // 'alt'键的虚拟键码
                        inputs[0].ki.dwFlags = 0; // 表示按下按键

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
                        inputs[1].ki.dwFlags = 0; // 表示按下按键

                        // 第二个按键 '传入的字符' 的输入结构体
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                        inputs[2].ki.dwFlags = 0; // 表示按下按键
                        // 发送输入，同时按下'alt'，"shift',和'指定参数'键
                        SendInput(3, inputs, sizeof(INPUT));  // 按下

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        break;
                    }
                }
            }
        }

            // 如果是win键
        else if(strcmp(key1, "win") ==0)
        {
            for (int i=0; i<len; i++)
            {
                // 如果第二个键与参数相符
                if (strcmp(button_list[i], key2) ==0)
                {
                    // 创建一个输入结构体并初始化
                    INPUT inputs[2] = {0};  // [2]表示两个元素执行两个按键点击，{0}初始化数组
                    // 第一个按键 'win' 的输入结构体
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_LWIN; // 'win'键的虚拟键码
                    inputs[0].ki.dwFlags = 0; // 表示按下按键

                    // 第二个按键 '传入的字符' 的输入结构体
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // '函数参数'键的虚拟键码
                    inputs[1].ki.dwFlags = 0; // 表示按下按键

                    // 发送输入，同时按下'win'和'指定参数'键
                    SendInput(2, inputs, sizeof(INPUT));
                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));
                    break;
                }
            }
        }
    }
}



/**
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 *
 * .............................................
 *          佛祖保佑             永无BUG
 */



void PressKey(const char *key) // 按键
{
    const char *symbol_list_not_shift_press[] = {"`", "[", "]", "\\", ";", "''", ",", ".", "/",
                                                 "-", "=", "，", "。", "’", "‘"};

    const char *symbol_list_need_shift_press[] = {"~", "{", "}", "|", ":", "\"\"", "<", ">", "?",
                                                  "_", "+","!", "@", "#", "$", "%", "^",
                                                  "&", "*", "(",")"};

    const char *chinese_symbol_shift_press[] = {"：", "“”", "《", "》", "？",
                                                "——", "！" , "￥", "……","（","）"};

/****************************虚键码列表********************************/
    int symbol_not_shift_code[] = {VK_OEM_3, VK_OEM_4, VK_OEM_6, VK_OEM_5, VK_OEM_1, VK_OEM_7, 188,
                                   190, VK_OEM_2, VK_OEM_MINUS, VK_OEM_PLUS, 188, 190, VK_OEM_7,
                                   VK_OEM_7};

    int symbol_need_shift_code[] = {VK_OEM_3, VK_OEM_4, VK_OEM_6, VK_OEM_5, VK_OEM_1, VK_OEM_7, 188,
                                    190, VK_OEM_2, VK_OEM_MINUS, VK_OEM_PLUS, 49,
                                    50, 51,52, 53, 54, 55, 56, 57, 48 };

    int chinese_symbol_shift_code[] = {VK_OEM_1, VK_OEM_7, 188,190, VK_OEM_2,
                                       VK_OEM_MINUS,  49,52, 53, 57, 48 };


/****************列表长度************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // 字母数字长度
    int symbol_not_shift_len = sizeof (symbol_list_not_shift_press)/sizeof(symbol_list_not_shift_press[0]); // 字符长度
    int symbol_need_shift_len = sizeof (symbol_list_need_shift_press)/sizeof (symbol_list_need_shift_press[0]); // 字符数组长度
    int function_keys_list_len = sizeof (function_keys_list)/sizeof (function_keys_list[0]);  // 功能键数组长度
    int chinese_symbol_shift_press_len = sizeof (chinese_symbol_shift_press)/sizeof (chinese_symbol_shift_press[0]);  // 中文字符数组列表长度


    for (int i = 0; i<alphabet_list_len; i++)
    {
        // 检查数组的字符是否与传入的参数一样(判断字母) 如果都没进入下一个循环
        if (strcmp(key, alphabet_list[i])==0)
        {
            INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

            input.type = INPUT_KEYBOARD; // 指定 input 的类型为键盘输入
            input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
            input.ki.time = 0; // 时间戳置为 0
            input.ki.dwExtraInfo = 0; // 额外信息置为 0

            // 模拟按下目标键
            input.ki.wVk = alphabet_code[i]; // 指定模拟按下的键为 目标 键
            input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
            SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统

            // 模拟释放目标键
            input.ki.wVk = alphabet_code[i]; // 指定模拟释放的键仍然是 目标 键
            input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
            break;
        }
    }

    for (int i=0; i<function_keys_list_len; i++)
    {
        // 是否与传入的参数一样 (判断功能键)
        if (strcmp(key, function_keys_list[i])==0)
        {
            INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

            input.type = INPUT_KEYBOARD; // 指定 input 的类型为键盘输入
            input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
            input.ki.time = 0; // 时间戳置为 0
            input.ki.dwExtraInfo = 0; // 额外信息置为 0

            // 模拟按下目标键
            input.ki.wVk = function_code[i]; // 指定模拟按下的键为 目标 键
            input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
            SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统

            input.ki.wVk = function_code[i]; // 指定模拟释放的键仍然是 目标 键
            input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
            break;
        }
    }

    for (int i=0; i< symbol_not_shift_len; i++)
    {
        // 是否与传入的参数一样 (判断无需按shift按键的符号)
        if (strcmp(key, symbol_list_not_shift_press[i])==0)
        {
            INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

            input.type = INPUT_KEYBOARD; // 指定 input 的类型为键盘输入
            input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
            input.ki.time = 0; // 时间戳置为 0
            input.ki.dwExtraInfo = 0; // 额外信息置为 0

            // 模拟按下目标键
            input.ki.wVk = symbol_not_shift_code[i]; // 指定模拟按下的键为 目标 键
            input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
            SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统

            input.ki.wVk = symbol_not_shift_code[i]; // 指定模拟释放的键仍然是 目标 键
            input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
            break;
        }
    }

    for (int i=0; i<symbol_need_shift_len; i++)
    {
        // 需要按shift的符合
        if (strcmp(key, symbol_list_need_shift_press[i])==0)
        {
            // 创建两个输入结构体并初始化
            INPUT inputs[2] = {0};

            // 第一个按键 'shift' 的输入结构体
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
            inputs[0].ki.dwFlags = 0; // 表示按下按键

            // 第二个按键 '目标参数' 的输入结构体
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = symbol_need_shift_code[i]; // '目标参数'键的虚拟键码
            inputs[1].ki.dwFlags = 0; // 表示按下按键
            SendInput(2, inputs, sizeof (INPUT));  // 发生指令按下shift与参数按键

            inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            SendInput(2, inputs, sizeof(INPUT));  // 同时释放
            break;
        }
    }

    for (int i=0; i<chinese_symbol_shift_press_len; i++)
    {
        // 中文字符判断
        if (strcmp(key, chinese_symbol_shift_press[i])==0)
        {
            // 创建两个输入结构体并初始化
            INPUT inputs[2] = {0};

            // 第一个按键 'shift' 的输入结构体
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
            inputs[0].ki.dwFlags = 0; // 表示按下按键

            // 第二个按键 '目标参数' 的输入结构体
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = chinese_symbol_shift_code[i]; // '目标参数'键的虚拟键码
            inputs[1].ki.dwFlags = 0; // 表示按下按键
            SendInput(2, inputs, sizeof (INPUT));  // 发生指令按下shift与参数按键

            inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            SendInput(2, inputs, sizeof(INPUT));  // 同时释放
            break;
        }
    }

}


void WriteStr(const char str_print[], int str_size)
{
    bool shift_up = false;

    const char *symbol_list_not_shift_press[] = {"`", "[", "]", "\\", ";", "''", ",", ".", "/",
                                                 "-", "=", "，", "。", "’", "‘"};

    const char *symbol_list_need_shift_press[] = {"~", "{", "}", "|", ":", "\"\"", "<", ">", "?",
                                                  "_", "+","!", "@", "#", "$", "%", "^",
                                                  "&", "*", "(",")"};

/****************************虚键码列表********************************/


    int symbol_not_shift_code[] = {VK_OEM_3, VK_OEM_4, VK_OEM_6, VK_OEM_5, VK_OEM_1, VK_OEM_7, 188,
                                   190, VK_OEM_2, VK_OEM_MINUS, VK_OEM_PLUS, 188, 190, VK_OEM_7,
                                   VK_OEM_7};

    int symbol_need_shift_code[] = {VK_OEM_3, VK_OEM_4, VK_OEM_6, VK_OEM_5, VK_OEM_1, VK_OEM_7, 188,
                                    190, VK_OEM_2, VK_OEM_MINUS, VK_OEM_PLUS, 49,
                                    50, 51,52, 53, 54, 55, 56, 57, 48 };


    /****************列表长度************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // 字母数字长度
    int symbol_not_shift_len = sizeof (symbol_list_not_shift_press)/sizeof(symbol_list_not_shift_press[0]); // 字符长度
    int symbol_need_shift_len = sizeof (symbol_list_need_shift_press)/sizeof (symbol_list_need_shift_press[0]); // 字符数组长度

    /****************************** 执行部分 ************************************/
    // 循环遍历输入字符串中的每一个字符
    for (int i = 0; i < str_size; i++)
    {
        char current_char = str_print[i];  // 将字符存储到字符变量

        // 处理字母
        for (int alp = 0; alp < alphabet_list_len; alp++)
        {
            // 检查是否为小写字母
            if (tolower(current_char) == alphabet_list[alp][0])
            {
                // 检查是否为大写字母
                bool is_uppercase = isupper(current_char); // 如果是大写

                if (is_uppercase)  // 如果有大写字母
                {
                    INPUT inputs[2] = {0};  // 设置两个按键
                    // 如果是大写字母，则首先模拟按下 Shift 键
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
                    inputs[0].ki.dwFlags = 0; // 表示按下按键

                    // 模拟按下目标键
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = alphabet_code[alp]; // 目标键的虚拟键码
                    inputs[1].ki.dwFlags = 0; // 表示按下按键
                    SendInput(2, inputs, sizeof(INPUT));  // 发送按键事件给系统
                    shift_up = true;  // shift被按下

                    // 释放 Shift 键和目标键
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));  // 再次发送按键事件给系统
                    shift_up = false;  // shift被释放
                }
                else
                {
                    // 如果是小写字母，则直接模拟按下目标键
                    INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

                    input.type = INPUT_KEYBOARD;
                    input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
                    input.ki.time = 0; // 时间戳置为 0
                    input.ki.dwExtraInfo = 0; // 额外信息置为 0

                    // 模拟按下目标键
                    input.ki.wVk = alphabet_code[alp]; // 指定模拟按下的键为 目标 键
                    input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
                    SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统
                    shift_up = true;  // shift被按下

                    // 模拟释放目标键
                    input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
                    SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
                    shift_up = false;  // shift被释放
                }
                break;
            }
        }


        for (int syb_no_shift=0; syb_no_shift< symbol_not_shift_len; syb_no_shift++)
        {
            // 是否与传入的参数一样 (判断无需按shift按键的符号)
            if (current_char == symbol_list_not_shift_press[syb_no_shift][0])  // 取出当前字符与中的字符与参数传入的字符进行比较
            {
                INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

                input.type = INPUT_KEYBOARD; // 指定 input 的类型为键盘输入
                input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
                input.ki.time = 0; // 时间戳置为 0
                input.ki.dwExtraInfo = 0; // 额外信息置为 0

                // 模拟按下目标键
                input.ki.wVk = symbol_not_shift_code[syb_no_shift]; // 指定模拟按下的键为 目标 键
                input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
                SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统
                shift_up = true;  // shift被按下

                input.ki.wVk = symbol_not_shift_code[syb_no_shift]; // 指定模拟释放的键仍然是 目标 键
                input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
                SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
                shift_up = false;  // shift被释放
                break;
            }
            // 处理空格
            if (current_char == ' ')
            {
                // 模拟按下空格键
                INPUT input; // 声明一个 INPUT 结构体变量 input，用于描述按键事件

                input.type = INPUT_KEYBOARD;
                input.ki.wScan = 0; // 扫描码置为 0，通常不需要使用
                input.ki.time = 0; // 时间戳置为 0
                input.ki.dwExtraInfo = 0; // 额外信息置为 0


                input.ki.wVk = VK_SPACE; // 指定模拟按下的键为 空格 键
                input.ki.dwFlags = 0; // 指定键盘按下事件，dwFlags 为 0
                SendInput(1, &input, sizeof(INPUT)); // 发送按键事件给系统
                shift_up = true;  // shift被按下

                // 模拟释放空格键
                input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
                SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
                shift_up = false;  // shift被释放
                break;
            }
        }

        for (int syb_need_shift=0; syb_need_shift< symbol_need_shift_len; syb_need_shift++)
        {
            // 是否与传入的参数一样 (判断需按shift按键的符号功能)
            if (current_char == symbol_list_need_shift_press[syb_need_shift][0])  // 取出当前字符与中的字符与参数传入的字符进行比较
            {
                // 创建两个输入结构体并初始化
                INPUT inputs[2] = {0};

                // 第一个按键 'shift' 的输入结构体
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_SHIFT; // 'shift'键的虚拟键码
                inputs[0].ki.dwFlags = 0; // 表示按下按键

                // 第二个按键 '目标参数' 的输入结构体
                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = symbol_need_shift_code[syb_need_shift]; // '目标参数'键的虚拟键码
                inputs[1].ki.dwFlags = 0; // 表示按下按键
                SendInput(2, inputs, sizeof (INPUT));  // 发生指令按下shift与参数按键
                shift_up = true;  // shift被按下

                inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                SendInput(2, inputs, sizeof(INPUT));  // 同时释放
                shift_up = false;  // shift被释放
                break;
            }
        }
    }
    if (!shift_up)
    {
        // 定义INPUT结构体
        INPUT input_shift = {0};
        input_shift.type = INPUT_KEYBOARD;  // 指定输入类型为键盘

        // 模拟释放Shift键
        input_shift.ki.wVk = VK_SHIFT;       // 设置虚拟键码为Shift
        input_shift.ki.dwFlags = KEYEVENTF_KEYUP;  // 指定键盘释放事件

        // 发送键盘释放事件
        SendInput(1, &input_shift, sizeof(INPUT));
    }
}

void copy_str_in(copy_str_structs self)  // 复制到剪切板的函数，后续包裹在CopyStr函数中
{
    if (OpenClipboard(NULL))
    {
        // 清空剪切板内容
        EmptyClipboard();

        // 分配内存并将文本内容复制到全局内存块
        HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, strlen(self.textToCopy) + 1); // +1是为了包含字符串的结尾 null 字符
        if (hglbCopy != NULL) {
            LPVOID lpCopy = GlobalLock(hglbCopy);
            strcpy((char*)lpCopy, self.textToCopy);
            GlobalUnlock(hglbCopy);

            // 将全局内存块设置为剪切板内容
            SetClipboardData(CF_TEXT, hglbCopy);
        }

        // 关闭剪切板
        CloseClipboard();
    }
}

void CopyStr(const char *str)   // 复制字符窜到剪切板
{  // 复制字符窜到剪切板
    copy_str_structs self = {str, copy_str_in};
    self.copy_str_in(self);
}

typedef struct {
    char* text; // 指向剪贴板文本的指针
    size_t length; // 文本长度
} ClipboardText;

PasteStrStructs PasteStr()
{
//    PasteStrStructs str = PasteStr();
//    printf("%s", str.text);
//    FreePasteStr(&str);

    PasteStrStructs result = {NULL, 0};

    if (OpenClipboard(NULL)) {
        HANDLE hClipboardData = GetClipboardData(CF_TEXT);
        if (hClipboardData != NULL) {
            char* clipboardText = (char*)GlobalLock(hClipboardData);
            if (clipboardText != NULL) {
                result.length = strlen(clipboardText);
                result.text = (char*)malloc(result.length + 1);
                if (result.text != NULL) {
                    strcpy(result.text, clipboardText);
                }
            }
            GlobalUnlock(hClipboardData);
        }
        CloseClipboard();
    }

    if (result.text == NULL) {
        result.text = (char*)malloc(1);
        result.text[0] = '\0'; // 如果无法获取文本，设置为空字符串
        result.length = 0;
    }

    return result;
}

void FreePasteStr(PasteStrStructs * clipboardText)
{
    if (clipboardText->text != NULL) {
        free(clipboardText->text);
        clipboardText->text = NULL;
        clipboardText->length = 0;
    }
}

/************** 快捷键注册 ***********************/

// 定义全局变量来保存钩子句柄
HHOOK hHook = NULL;      // HHOOK 类型用于保存钩子句柄;

HotKeyList *head = NULL;  // 列表头指针

Func_List fs;  // 实例化函数列表结构体


// 键盘钩子的回调函数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    const char *button_list[] = {"a", "b", "c", "d", "e", "f", "g",
                                 "h", "i", "j", "k", "l", "m",
                                 "n", "o", "p", "q", "r", "s",
                                 "t", "u", "v", "w", "x", "y", "z",  // 26字母
                                 "0", "1", "2", "3", "4", "5", "6",
                                 "7", "8", "9", "ctrl", "alt", "shift", "enter",
                                 "F1", "F2", "F3", "F4", "F5","F6",
                                 "F7", "F8", "F9", "F10", "F11", "F12", "space", "esc"};  // 按键列

    int button_code_list[] = {65, 66, 67, 68, 69, 70,
                              71, 72, 73, 74, 75, 76,
                              77, 78, 79, 80, 81, 82,
                              83, 84, 85, 86, 87, 88,
                              89, 90, 48, 49, 50, 51,
                              52, 53, 54, 55, 56, 57, VK_CONTROL,
                              VK_MENU, VK_SHIFT, VK_RETURN, VK_F1, VK_F2, VK_F3,
                              VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
                              VK_F11, VK_F12, VK_SPACE, VK_ESCAPE};  // 虚拟键码

    int button_list_len = sizeof(button_list) / sizeof(button_list[0]);  // 按键列表长度
    int key1_code, key2_code, key3_code, key4_code;  // 定义四个快捷键的码



    // 遍历快捷键链表，*current = head存放列表头指针不为NULL时这个值就访问指向下一个实例的自己
    for (HotKeyList *current = head; current != NULL; current = current->next)
    {
        // 四个快捷键  //
        if (current ->data.key1!=NULL && current ->data.key2!=NULL && current ->data.key3!=NULL && current ->data.key4!=NULL)
        {
            // 四个快捷键
            for (int i = 0; i < button_list_len; i++)
            {
                if (strcmp(current->data.key1, button_list[i]) == 0)
                {
                    key1_code = button_code_list[i];
                }
                else if (strcmp(current->data.key2, button_list[i]) == 0)
                {
                    key2_code = button_code_list[i];
                }
                else if (strcmp(current->data.key3, button_list[i]) == 0)
                {
                    key3_code = button_code_list[i];
                }
                else if (strcmp(current->data.key4, button_list[i]) == 0)
                {
                    key4_code = button_code_list[i];
                }
            }

            // 检查钩子操作是否成功
            if (nCode >= 0)
            {
                // 获取键盘钩子结构体
                PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                // 检查是否为键盘按下消息，且同时按下注册的快捷键
                if (
                        GetAsyncKeyState(key1_code) & 0x8000 &&  // 检查key1参数键是否按下
                        GetAsyncKeyState(key2_code) & 0x8000 &&  // 检查key2参数键是否按下
                        GetAsyncKeyState(key3_code) & 0x8000 &&  // 检查key3参数键是否按下
                        pKey->vkCode == key4_code)                // 检查第四个键是否按下
                {
                    /*** ctrl alt shift ***/
                    if (key1_code == VK_CONTROL && key2_code == VK_MENU && key3_code == VK_SHIFT)
                    {
                        for (int four_key_func=0; four_key_func<fs.size_four_key_ctrl_alt_shift; four_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.four_key_name_ctrl_alt_shift[four_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.four_key_name_ctrl_alt_shift[four_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_four_key_ctrl_alt_shift[four_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        // ctrl shift alt  //
                    else if (key1_code == VK_CONTROL && key2_code == VK_SHIFT && key3_code == VK_MENU)
                    {
                        for (int four_key_func=0; four_key_func<fs.size_four_key_ctrl_shift_alt; four_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.four_key_name_ctrl_shift_alt[four_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.four_key_name_ctrl_shift_alt[four_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_four_key_ctrl_shift_alt[four_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        // alt ctrl shift //
                    else if (key1_code == VK_MENU && key2_code == VK_CONTROL && key3_code == VK_SHIFT)
                    {
                        for (int four_key_func=0; four_key_func<fs.size_four_key_alt_ctrl_shift; four_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.four_key_name_alt_ctrl_shift[four_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.four_key_name_alt_ctrl_shift[four_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_four_key_alt_ctrl_shift[four_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        // alt shift ctrl //
                    else if (key1_code == VK_MENU && key2_code == VK_SHIFT && key3_code == VK_CONTROL)
                    {
                        for (int four_key_func=0; four_key_func<fs.size_four_key_alt_shift_ctrl; four_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.four_key_name_alt_shift_ctrl[four_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.four_key_name_alt_shift_ctrl[four_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_four_key_alt_shift_ctrl[four_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        // shift ctrl alt  //
                    else if (key1_code == VK_SHIFT && key2_code == VK_CONTROL && key3_code == VK_MENU)
                    {
                        for (int four_key_func=0; four_key_func<fs.size_four_key_shift_ctrl_alt; four_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.four_key_name_shift_ctrl_alt[four_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.four_key_name_shift_ctrl_alt[four_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_four_key_shift_ctrl_alt[four_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        // shift alt ctrl  //
                    else if (key1_code == VK_MENU && key2_code == VK_MENU && key3_code == VK_CONTROL)
                    {
                        for (int four_key_func=0; four_key_func<fs.size_four_key_shift_alt_ctrl; four_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.four_key_name_shift_alt_ctrl[four_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.four_key_name_shift_alt_ctrl[four_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_four_key_shift_alt_ctrl[four_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

            // 如果快捷键只有三个
        else if (current->data.key1 != NULL && current->data.key2 != NULL && current->data.key3 != NULL && current->data.key4 == NULL)
        {

            for (int i = 0; i < button_list_len; i++)
            {
                if (strcmp(current->data.key1, button_list[i]) == 0)
                {
                    key1_code = button_code_list[i];
                }
                else if (strcmp(current->data.key2, button_list[i]) == 0)
                {
                    key2_code = button_code_list[i];
                }
                else if (strcmp(current->data.key3, button_list[i]) == 0)
                {
                    key3_code = button_code_list[i];
                }
            }

            // 检查钩子操作是否成功
            if (nCode >= 0)
            {
                // 获取键盘钩子结构体
                PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;
                // 检查是否为键盘按下消息，且同时按下注册的快捷键
                if (GetAsyncKeyState(key1_code) & 0x8000 &&  // 检查key1参数键是否按下
                    GetAsyncKeyState(key2_code) & 0x8000 &&  // 检查key2参数键是否按下
                    pKey->vkCode == key3_code)                // 检查第三个键是否按下
                {
                    /************** ctrl+alt ***************/
                    if (key1_code== VK_CONTROL && key2_code == VK_MENU)
                    {
                        for (int three_key_func=0; three_key_func<fs.size_three_ctrl_alt; three_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.three_key_name_ctrl_alt[three_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.three_key_name_ctrl_alt[three_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_three_key_ctrl_alt[three_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        /*************** ctrl+shift *****************/
                    else if (key1_code==VK_CONTROL && key2_code == VK_SHIFT)
                    {
                        for (int three_key_func=0; three_key_func<fs.size_three_ctrl_shift; three_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.three_key_name_ctrl_shift[three_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        printf("name:%s, code:%d\n", button_list[key_end_code], button_code_list[key_end_code]);
                                        if (strcmp(fs.three_key_name_ctrl_shift[three_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_three_key_ctrl_shift[three_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        /************ alt+ctrl *************/
                    else if (key1_code==VK_MENU && key2_code==VK_CONTROL)
                    {
                        for (int three_key_func=0; three_key_func<fs.size_three_alt_ctrl; three_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.three_key_name_alt_ctrl[three_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.three_key_name_alt_ctrl[three_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_three_key_alt_ctrl[three_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }
                        /*********** alt+shift ***********/
                    else if (key1_code==VK_MENU && key2_code==VK_SHIFT)
                    {
                        for (int three_key_func=0; three_key_func<fs.size_three_alt_shift; three_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.three_key_name_alt_shift[three_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.three_key_name_alt_shift[three_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_three_key_alt_shift[three_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }

                        /************* shift+ctrl ************/
                    else if (key1_code==VK_SHIFT && key2_code==VK_CONTROL)
                    {
                        for (int three_key_func=0; three_key_func<fs.size_three_shift_ctrl; three_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.three_key_name_shift_ctrl[three_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.three_key_name_shift_ctrl[three_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_three_key_shift_ctrl[three_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    /********** shift+alt ***********/
                    if (key1_code==16 && key2_code==18)
                    {
                        for (int three_key_func=0; three_key_func<fs.size_three_shift_alt; three_key_func++)
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                            {
                                if (strcmp(fs.three_key_name_shift_alt[three_key_func], button_list[key_end_code])==0)  // 获取键位码
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                    {
                                        if (strcmp(fs.three_key_name_shift_alt[three_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_three_key_shift_alt[three_key_func]();  // ctrl函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    return CallNextHookEx(NULL, nCode, wParam, lParam);
                }
            }
        }

            // 如果只注册两个快捷键
        else if (current->data.key1 != NULL && current->data.key2 != NULL && current->data.key3 == NULL && current->data.key4 == NULL)
        {
            for (int i = 0; i < button_list_len; i++)
            {
                if (strcmp(current->data.key1, button_list[i]) == 0)  // 查看传入的值与键位列表对应获取虚键码
                {
                    key1_code = button_code_list[i];
                }
                else if (strcmp(current->data.key2, button_list[i]) == 0)
                {
                    key2_code = button_code_list[i];
                }

                // 检查钩子操作是否成功
                if (nCode >= 0)
                {
                    // 获取键盘钩子结构体
                    PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                    // 检查是否为键盘按下消息，且同时按下注册的快捷键
                    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN &&  // 监听，第一个监听按键按下，第二个监听关于alt的按键按下
                                                GetAsyncKeyState(key1_code) & 0x8000 &&  // 检查key1参数键是否按下
                                                pKey->vkCode == key2_code)                // 检查第2个键是否按下
                    {//////////////////////////////////////////////
                        // 快捷键函数寻找
                        if (key1_code == VK_CONTROL)  // 第一个键是ctrl
                        {
                            for (int tow_key_func=0; tow_key_func<fs.size_two_ctrl; tow_key_func++)
                            {
                                for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                                {
                                    if (strcmp(fs.tow_key_name_ctrl[tow_key_func], button_list[key_end_code])==0)  // 获取键位码,快捷键与虚键码对应
                                    {
                                        if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                        {
                                            if (strcmp(fs.tow_key_name_ctrl[tow_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                            {
                                                fs.funcArray_two_key_ctrl[tow_key_func]();  // ctrl函数
                                                return CallNextHookEx(NULL, nCode, wParam, lParam);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else if (key1_code == VK_MENU)  // 如果为alt
                        {
                            for (int tow_key_func=0; tow_key_func<fs.size_two_alt; tow_key_func++)
                            {
                                for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                                {
                                    if (strcmp(fs.tow_key_name_alt[tow_key_func], button_list[key_end_code])==0)  // 获取键位码
                                    {
                                        if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                        {
                                            if (strcmp(fs.tow_key_name_alt[tow_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                            {
                                                fs.funcArray_two_key_alt[tow_key_func]();
                                                return CallNextHookEx(NULL, nCode, wParam, lParam);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else if (key1_code==VK_SHIFT)  // 如果是shift
                        {
                            for (int tow_key_func=0; tow_key_func<fs.size_two_shift; tow_key_func++)
                            {
                                for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 按键码
                                {
                                    if (strcmp(fs.tow_key_name_shift[tow_key_func], button_list[key_end_code])==0)  // 获取键位码
                                    {
                                        if (pKey->vkCode == button_code_list[key_end_code])  // 如果虚键码相同
                                        {
                                            if (strcmp(fs.tow_key_name_shift[tow_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                            {
                                                fs.funcArray_two_key_shift[tow_key_func]();
                                                return CallNextHookEx(NULL, nCode, wParam, lParam);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

            // 只按下一个快捷键
        else if (current->data.key1 != NULL && current->data.key2 == NULL && current->data.key3 == NULL && current->data.key4 == NULL)
        {
            for (int i = 0; i < button_list_len; i++)
            {
                if (strcmp(current->data.key1, button_list[i]) == 0)
                {
                    key1_code = button_code_list[i];
                }
                // 检查钩子操作是否成功
                if (nCode >= 0)
                {
                    // 获取键盘钩子结构体
                    PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                    if (wParam == WM_KEYDOWN &&
                        pKey->vkCode == key1_code)                // 检查第1个键是否按下
                    {
                        for (int one_key_func=0; one_key_func<fs.size_one; one_key_func++)  // 遍历数组函数
                        {
                            for (int key_end_code=0; key_end_code<button_list_len; key_end_code++)  // 先获取键位码，与按下的·按键比较
                            {
                                if (strcmp(fs.one_key_name[one_key_func], button_list[key_end_code])==0)  // 如果匹配
                                {
                                    if (pKey->vkCode == button_code_list[key_end_code])
                                    {
                                        if (strcmp(fs.one_key_name[one_key_func], button_list[key_end_code])==0)  // 获取按键的索引，索引对应的函数
                                        {
                                            fs.funcArray_one_key[one_key_func]();  // 回调函数
                                            return CallNextHookEx(NULL, nCode, wParam, lParam);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


// 添加快捷键的函数
void AddHotKey(const char *key1, const char *key2, const char *key3, const char *key4, void (*target_void_func)())
{
    static int four_key_func_size_ctrl_alt_shift = 1;  // 四个快捷键
    static int four_key_func_size_ctrl_shift_alt = 1;
    static int four_key_func_size_alt_ctrl_shift = 1;
    static int four_key_func_size_alt_shift_ctrl = 1;
    static int four_key_func_size_shift_ctrl_alt = 1;
    static int four_key_func_size_shift_alt_ctrl = 1;

    static int three_key_func_size_ctrl_alt = 1;  // 三个快捷键
    static int three_key_func_size_ctrl_shift = 1;
    static int three_key_func_size_alt_ctrl = 1;
    static int three_key_func_size_alt_shift = 1;
    static int three_key_func_size_shift_ctrl = 1;
    static int three_key_func_size_shift_alt = 1;

    static int two_key_func_size_ctrl = 1;  // 双快捷键
    static int two_key_func_size_alt = 1;
    static int two_key_func_size_shift = 1;

    static int one_key_func_size = 1;  // 单快捷键

    // 注册四个快捷键
    if (key1 !=NULL && key2 !=NULL && key3 !=NULL && key4 !=NULL)
    {
        if (strcmp(key1, "ctrl")==0 && strcmp(key2, "alt") ==0 && strcmp(key3, "shift") ==0)
            // ctrl+alt+shift
        {
            if (four_key_func_size_ctrl_alt_shift ==1)
            {  // 如果函数数组大小为1那么首次分配内存
                fs.funcArray_four_key_ctrl_alt_shift = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_four_key_ctrl_alt_shift == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *four_keys_temp = (FunctionPtr *) realloc(fs.funcArray_four_key_ctrl_alt_shift, four_key_func_size_ctrl_alt_shift * sizeof(FunctionPtr));
                // 如果分配失败
                if (four_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_four_key_ctrl_alt_shift);
                    fs.funcArray_four_key_ctrl_alt_shift = NULL;
                    return;
                }
                fs.funcArray_four_key_ctrl_alt_shift = four_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_four_key_ctrl_alt_shift[four_key_func_size_ctrl_alt_shift-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_four_key_ctrl_alt_shift = four_key_func_size_ctrl_alt_shift;
            fs.four_key_name_ctrl_alt_shift[four_key_func_size_ctrl_alt_shift-1] = key4;  // 给每个数组元素加上对应的按键(最后一个按键确认调用的哪个函数)
            four_key_func_size_ctrl_alt_shift++;  // 每次完成以后自增
        }

            // ctrl+shift_alt
        else if (strcmp(key1, "ctrl")==0 && strcmp(key2, "shift") ==0 && strcmp(key3, "alt") ==0)
        {
            if (four_key_func_size_ctrl_shift_alt ==1)
            {  // 如果函数数组大小为1那么首次分配内存
                fs.funcArray_four_key_ctrl_shift_alt = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_four_key_ctrl_shift_alt == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *four_keys_temp = (FunctionPtr *) realloc(fs.funcArray_four_key_ctrl_shift_alt, four_key_func_size_ctrl_shift_alt * sizeof(FunctionPtr));
                // 如果分配失败
                if (four_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_four_key_ctrl_shift_alt);
                    fs.funcArray_four_key_ctrl_shift_alt = NULL;
                    return;
                }
                fs.funcArray_four_key_ctrl_shift_alt = four_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_four_key_ctrl_shift_alt[four_key_func_size_ctrl_shift_alt-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_four_key_ctrl_shift_alt = four_key_func_size_ctrl_shift_alt;
            fs.four_key_name_ctrl_shift_alt[four_key_func_size_ctrl_shift_alt-1] = key4;  // 给每个数组元素加上对应的按键(最后一个按键确认调用的哪个函数)
            four_key_func_size_ctrl_shift_alt++;  // 每次完成以后自增
        }

            // alt+ctrl+shift
        else if (strcmp(key1, "alt")==0 && strcmp(key2, "ctrl") ==0 && strcmp(key3, "shift") ==0)
        {
            if (four_key_func_size_alt_ctrl_shift ==1)
            {  // 如果函数数组大小为1那么首次分配内存
                fs.funcArray_four_key_alt_ctrl_shift = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_four_key_alt_ctrl_shift == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *four_keys_temp = (FunctionPtr *) realloc(fs.funcArray_four_key_alt_ctrl_shift, four_key_func_size_alt_ctrl_shift * sizeof(FunctionPtr));
                // 如果分配失败
                if (four_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_four_key_alt_ctrl_shift);
                    fs.funcArray_four_key_alt_ctrl_shift = NULL;
                    return;
                }
                fs.funcArray_four_key_alt_ctrl_shift = four_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_four_key_alt_ctrl_shift[four_key_func_size_alt_ctrl_shift-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_four_key_alt_ctrl_shift = four_key_func_size_alt_ctrl_shift;
            fs.four_key_name_alt_ctrl_shift[four_key_func_size_alt_ctrl_shift-1] = key4;  // 给每个数组元素加上对应的按键(最后一个按键确认调用的哪个函数)
            four_key_func_size_alt_ctrl_shift++;  // 每次完成以后自增
        }

            // alt_shift_ctrl
        else if (strcmp(key1, "alt")==0 && strcmp(key2, "shift") ==0 && strcmp(key3, "ctrl") ==0)
        {
            if (four_key_func_size_alt_shift_ctrl ==1)
            {  // 如果函数数组大小为1那么首次分配内存
                fs.funcArray_four_key_alt_shift_ctrl = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_four_key_alt_shift_ctrl == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *four_keys_temp = (FunctionPtr *) realloc(fs.funcArray_four_key_alt_shift_ctrl, four_key_func_size_alt_shift_ctrl * sizeof(FunctionPtr));
                // 如果分配失败
                if (four_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_four_key_alt_shift_ctrl);
                    fs.funcArray_four_key_alt_shift_ctrl = NULL;
                    return;
                }
                fs.funcArray_four_key_alt_shift_ctrl = four_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_four_key_alt_shift_ctrl[four_key_func_size_alt_shift_ctrl-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_four_key_alt_shift_ctrl = four_key_func_size_alt_shift_ctrl;
            fs.four_key_name_alt_shift_ctrl[four_key_func_size_alt_shift_ctrl-1] = key4;  // 给每个数组元素加上对应的按键(最后一个按键确认调用的哪个函数)
            four_key_func_size_alt_shift_ctrl++;  // 每次完成以后自增
        }

            // shift ctrl alt
        else if (strcmp(key1, "shift")==0 && strcmp(key2, "ctrl") ==0 && strcmp(key3, "alt") ==0)
        {
            if (four_key_func_size_shift_ctrl_alt ==1)
            {  // 如果函数数组大小为1那么首次分配内存
                fs.funcArray_four_key_shift_ctrl_alt = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_four_key_shift_ctrl_alt == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *four_keys_temp = (FunctionPtr *) realloc(fs.funcArray_four_key_shift_ctrl_alt, four_key_func_size_shift_ctrl_alt * sizeof(FunctionPtr));
                // 如果分配失败
                if (four_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_four_key_shift_ctrl_alt);
                    fs.funcArray_four_key_shift_ctrl_alt = NULL;
                    return;
                }
                fs.funcArray_four_key_shift_ctrl_alt = four_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_four_key_shift_ctrl_alt[four_key_func_size_shift_ctrl_alt-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_four_key_shift_ctrl_alt = four_key_func_size_shift_ctrl_alt;
            fs.four_key_name_shift_ctrl_alt[four_key_func_size_shift_ctrl_alt-1] = key4;  // 给每个数组元素加上对应的按键(最后一个按键确认调用的哪个函数)
            four_key_func_size_shift_ctrl_alt++;  // 每次完成以后自增
        }

            // shift alt ctrl
        else if (strcmp(key1, "shift")==0 && strcmp(key2, "alt") ==0 && strcmp(key3, "ctrl") ==0)
        {
            if (four_key_func_size_shift_alt_ctrl ==1)
            {  // 如果函数数组大小为1那么首次分配内存
                fs.funcArray_four_key_shift_alt_ctrl = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_four_key_shift_alt_ctrl == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *four_keys_temp = (FunctionPtr *) realloc(fs.funcArray_four_key_shift_alt_ctrl, four_key_func_size_shift_alt_ctrl * sizeof(FunctionPtr));
                // 如果分配失败
                if (four_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_four_key_shift_alt_ctrl);
                    fs.funcArray_four_key_shift_alt_ctrl = NULL;
                    return;
                }
                fs.funcArray_four_key_shift_alt_ctrl = four_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_four_key_shift_alt_ctrl[four_key_func_size_shift_alt_ctrl-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_four_key_shift_alt_ctrl = four_key_func_size_shift_alt_ctrl;
            fs.four_key_name_shift_alt_ctrl[four_key_func_size_shift_alt_ctrl-1] = key4;  // 给每个数组元素加上对应的按键(最后一个按键确认调用的哪个函数)
            four_key_func_size_shift_alt_ctrl++;  // 每次完成以后自增
        }
    }

        // 三快捷键 //
    else if(key1 !=NULL && key2 !=NULL && key3 !=NULL && key4 ==NULL)
    {
        // ctrl+alt //
        if (strcmp(key1, "ctrl")==0 && strcmp(key2, "alt")==0)  // 如果是ctrl+alt+key
        {
            if (three_key_func_size_ctrl_alt ==1)
            {
                fs.funcArray_three_key_ctrl_alt = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_three_key_ctrl_alt == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *three_keys_temp = (FunctionPtr *) realloc(fs.funcArray_three_key_ctrl_alt, three_key_func_size_ctrl_alt * sizeof(FunctionPtr));
                // 如果分配失败
                if (three_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_three_key_ctrl_alt);
                    fs.funcArray_three_key_ctrl_alt = NULL;
                    return;
                }
                fs.funcArray_three_key_ctrl_alt = three_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_three_key_ctrl_alt[three_key_func_size_ctrl_alt-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_three_ctrl_alt = three_key_func_size_ctrl_alt;  // 设置数组大小
            fs.three_key_name_ctrl_alt[three_key_func_size_ctrl_alt-1] = key3;  // 设置第三个快捷键
            three_key_func_size_ctrl_alt++;  // 每次完成以后自增
        }
            // ctrl+shift //
        else if (strcmp(key1, "ctrl")==0 && strcmp(key2, "shift")==0)
        {
            if (three_key_func_size_ctrl_shift ==1)
            {
                fs.funcArray_three_key_ctrl_shift = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_three_key_ctrl_shift == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *three_keys_temp = (FunctionPtr *) realloc(fs.funcArray_three_key_ctrl_shift, three_key_func_size_ctrl_shift * sizeof(FunctionPtr));
                // 如果分配失败
                if (three_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_three_key_ctrl_shift);
                    fs.funcArray_three_key_ctrl_shift = NULL;
                    return;
                }
                fs.funcArray_three_key_ctrl_shift = three_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_three_key_ctrl_shift[three_key_func_size_ctrl_shift-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_three_ctrl_shift = three_key_func_size_ctrl_shift;  // 传入大小
            fs.three_key_name_ctrl_shift[three_key_func_size_ctrl_shift-1] = key3;  // 传入按键
            three_key_func_size_ctrl_shift++;  // 每次完成以后自增
        }

            // alt+ctrl //
        else if (strcmp(key1, "alt")==0 && strcmp(key2, "shift")==0)
        {
            if (three_key_func_size_alt_ctrl ==1)
            {
                fs.funcArray_three_key_alt_ctrl = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_three_key_alt_ctrl == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *three_keys_temp = (FunctionPtr *) realloc(fs.funcArray_three_key_alt_ctrl, three_key_func_size_alt_ctrl * sizeof(FunctionPtr));
                // 如果分配失败
                if (three_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_three_key_alt_ctrl);
                    fs.funcArray_three_key_alt_ctrl = NULL;
                    return;
                }
                fs.funcArray_three_key_alt_ctrl = three_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_three_key_alt_ctrl[three_key_func_size_alt_ctrl-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_three_alt_ctrl = three_key_func_size_alt_ctrl;  // 设置大小
            fs.three_key_name_alt_ctrl[three_key_func_size_alt_ctrl-1] = key3;  // 这种最后一个案件
            three_key_func_size_alt_ctrl++;  // 每次完成以后自增
        }
            // alt+shift  //
        else if (strcmp(key1, "alt")==0 && strcmp(key2, "shift")==0)
        {
            if (three_key_func_size_alt_shift ==1)
            {
                fs.funcArray_three_key_alt_shift = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_three_key_alt_shift == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *three_keys_temp = (FunctionPtr *) realloc(fs.funcArray_three_key_alt_shift, three_key_func_size_alt_shift * sizeof(FunctionPtr));
                // 如果分配失败
                if (three_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_three_key_alt_shift);
                    fs.funcArray_three_key_alt_shift = NULL;
                    return;
                }
                fs.funcArray_three_key_alt_shift = three_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_three_key_alt_shift[three_key_func_size_alt_shift-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_three_alt_shift = three_key_func_size_alt_shift;
            fs.three_key_name_alt_shift[three_key_func_size_alt_shift-1] = key3;
            three_key_func_size_alt_shift++;  // 每次完成以后自增
        }

            // shift_ctrl //
        else if (strcmp(key1, "shift")==0 && strcmp(key2, "ctrl")==0)
        {
            if (three_key_func_size_shift_ctrl ==1)
            {
                fs.funcArray_three_key_shift_ctrl = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_three_key_shift_ctrl == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *three_keys_temp = (FunctionPtr *) realloc(fs.funcArray_three_key_shift_ctrl, three_key_func_size_shift_ctrl * sizeof(FunctionPtr));
                // 如果分配失败
                if (three_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_three_key_shift_ctrl);
                    fs.funcArray_three_key_shift_ctrl = NULL;
                    return;
                }
                fs.funcArray_three_key_shift_ctrl = three_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_three_key_shift_ctrl[three_key_func_size_shift_ctrl-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_three_shift_ctrl = three_key_func_size_shift_ctrl;
            fs.three_key_name_shift_ctrl[three_key_func_size_shift_ctrl-1] = key3;

            three_key_func_size_shift_ctrl++;  // 每次完成以后自增
        }
            // shift+alt //
        else if (strcmp(key1, "shift")==0 && strcmp(key2, "alt")==0)
        {
            if (three_key_func_size_shift_alt ==1)
            {
                fs.funcArray_three_key_shift_alt = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
                if (fs.funcArray_three_key_shift_alt == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            }
            else
            {
                FunctionPtr *three_keys_temp = (FunctionPtr *) realloc(fs.funcArray_three_key_shift_alt, three_key_func_size_shift_alt * sizeof(FunctionPtr));
                // 如果分配失败
                if (three_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_three_key_shift_alt);
                    fs.funcArray_three_key_shift_alt = NULL;
                    return;
                }
                fs.funcArray_three_key_shift_alt = three_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_three_key_shift_alt[three_key_func_size_shift_alt-1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_three_shift_alt = three_key_func_size_shift_alt;
            fs.three_key_name_shift_alt[three_key_func_size_shift_alt-1] = key3;
            three_key_func_size_shift_alt++;  // 每次完成以后自增
        }
    }


        // 两个快捷键
    else if(key1 !=NULL && key2 !=NULL && key3 ==NULL && key4 ==NULL)
    {
        if (strcmp(key1, "ctrl")==0)
        {
            if (two_key_func_size_ctrl == 1)
            {
                fs.funcArray_two_key_ctrl = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));  // 可用改为two_key_func_size，但是没必要了
                if (fs.funcArray_two_key_ctrl == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            } else {
                FunctionPtr *two_keys_temp = (FunctionPtr *) realloc(fs.funcArray_two_key_ctrl,two_key_func_size_ctrl * sizeof(FunctionPtr));
                // 如果分配失败
                if (two_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_two_key_ctrl);
                    fs.funcArray_two_key_ctrl = NULL;
                    return;
                }
                fs.funcArray_two_key_ctrl = two_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_two_key_ctrl[two_key_func_size_ctrl - 1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_two_ctrl = two_key_func_size_ctrl;  // 传递数组大小
            fs.tow_key_name_ctrl[two_key_func_size_ctrl-1] = key2;  // 将按键传入结构体名字数组
            two_key_func_size_ctrl++;  // 每次完成以后自增
        }
            // 如果是alt开头
        else if (strcmp(key1, "alt")==0)
        {
            if (two_key_func_size_alt == 1) {
                fs.funcArray_two_key_alt = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));  // 可用改为two_key_func_size，但是没必要了
                if (fs.funcArray_two_key_alt == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            } else
            {
                FunctionPtr *two_keys_temp = (FunctionPtr *) realloc(fs.funcArray_two_key_alt,two_key_func_size_alt * sizeof(FunctionPtr));
                // 如果分配失败
                if (two_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_two_key_alt);
                    fs.funcArray_two_key_alt = NULL;
                    return;
                }
                fs.funcArray_two_key_alt = two_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_two_key_alt[two_key_func_size_alt - 1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_two_alt = two_key_func_size_alt;  // 传递数组大小
            fs.tow_key_name_alt[two_key_func_size_alt-1] = key2;
            two_key_func_size_alt++;  // 每次完成以后自增
        }

            // shift开头 //
        else if (strcmp(key1, "shift")==0)
        {
            if (two_key_func_size_shift == 1) {
                fs.funcArray_two_key_shift = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));  // 可用改为two_key_func_size，但是没必要了
                if (fs.funcArray_two_key_shift == NULL) {
                    printf("内存分配失败\n");
                    return;
                }
            } else
            {
                FunctionPtr *two_keys_temp = (FunctionPtr *) realloc(fs.funcArray_two_key_shift,two_key_func_size_shift * sizeof(FunctionPtr));
                // 如果分配失败
                if (two_keys_temp == NULL) {
                    printf("分配内存失败,快捷键4");
                    // 保存原始指针以便释放
                    free(fs.funcArray_two_key_shift);
                    fs.funcArray_two_key_shift = NULL;
                    return;
                }
                fs.funcArray_two_key_shift = two_keys_temp; // 重新分配成功后更新指针
            }
            fs.funcArray_two_key_shift[two_key_func_size_shift - 1] = target_void_func;  // -1是因为数组索引从0开始
            fs.size_two_shift = two_key_func_size_shift;  // 传递数组大小
            fs.tow_key_name_shift[two_key_func_size_shift-1] = key2;
            two_key_func_size_shift++;  // 每次完成以后自增
        }
    }

        // 单个快捷键 //
    else if (key1 != NULL && key2 == NULL && key3 == NULL && key4 == NULL)
    {
        if (one_key_func_size == 1)
        {
            fs.funcArray_one_key = (FunctionPtr *) malloc(3 * sizeof(FunctionPtr));
            if (fs.funcArray_one_key == NULL) {
                printf("内存分配失败\n");
                return;
            }
        }
        else
        {
            FunctionPtr *one_keys_temp = (FunctionPtr *) realloc(fs.funcArray_one_key, one_key_func_size * sizeof(FunctionPtr));
            if (one_keys_temp == NULL) {
                printf("分配内存失败,快捷键1");
                free(fs.funcArray_one_key); // 释放原始内存
                fs.funcArray_one_key = NULL;
                return;
            }
            fs.funcArray_one_key = one_keys_temp; // 更新指针
        }
        // 确保使用更新后的 one_key_func_size
        fs.funcArray_one_key[one_key_func_size - 1] = target_void_func;
        fs.size_one = one_key_func_size;
        fs.one_key_name[one_key_func_size-1] = key1;
        one_key_func_size++; // 更新函数数量
    }

    // 快捷键注册部分
    HotKeyList *newNode = (HotKeyList *)malloc(sizeof(HotKeyList));  // 分配内存
    if (!newNode)
    {
        printf("内存分配失败\n");
        return;
    }
    newNode->data.key1 = key1;  // 设置快捷键
    newNode->data.key2 = key2;
    newNode->data.key3 = key3;
    newNode->data.key4 = key4;
//    newNode->data.function = target_void_func;  // 设置回调函数

    // newNode->next = head; 和 head = newNode; 是用来将新创建的节点 newNode 插入到链表中的头部，并更新链表的头部指针。
    newNode->next = head;  // 设置链表连接,将新节点的 next 指针指向当前链表的头部节点而原先链表的头部节点将成为第二个节点。
    head = newNode;  // 更新头指针,通过将 head 设置为 newNode，新节点成为了链表的新头部，也就是链表的第一个元素
    // 示例:node1 -> node2 -> NULL



}

void freeHotKeys()
{
    HotKeyList *current = head;
    HotKeyList *temp;
    // 遍历链表并释放每个节点的内存
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);  // 释放当前节点的内存
    }

    head = NULL;  // 清空头部指针

}

// 注册一个键盘低级钩子
void ListenHotKEy()
{
    // 监听快捷键循环函数
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);  // 安装低级键盘钩子

    MSG msg;          // MSG 结构体用于存储从消息队列中获取的消息


    // 进入消息循环
    while (GetMessage(&msg, NULL, 0, 0))  // 从消息队列中获取消息
    {
        TranslateMessage(&msg);           // 将虚拟键码转换成字符
        DispatchMessage(&msg);            // 分发消息到窗口过程
    }

}

void free_funcs()
{
    /**** 四个快捷键 ****/
    // 释放函数分配的内存

    // ctrl //
    if (fs.funcArray_four_key_ctrl_alt_shift !=NULL)  // 如果没有分配内存失败，释放内存
    {
        free(fs.funcArray_four_key_ctrl_alt_shift);
        fs.funcArray_four_key_ctrl_alt_shift = NULL;
    }
    if (fs.funcArray_four_key_ctrl_shift_alt !=NULL)  // 如果没有分配内存失败，释放内存
    {
        free(fs.funcArray_four_key_ctrl_shift_alt);
        fs.funcArray_four_key_ctrl_shift_alt = NULL;
    }

    // alt //
    if (fs.funcArray_four_key_alt_ctrl_shift !=NULL)  // 如果没有分配内存失败，释放内存
    {
        free(fs.funcArray_four_key_alt_ctrl_shift);
        fs.funcArray_four_key_alt_ctrl_shift = NULL;
    }
    if (fs.funcArray_four_key_alt_shift_ctrl !=NULL)  // 如果没有分配内存失败，释放内存
    {
        free(fs.funcArray_four_key_alt_shift_ctrl);
        fs.funcArray_four_key_alt_shift_ctrl = NULL;
    }

    // shift //
    if (fs.funcArray_four_key_shift_ctrl_alt !=NULL)  // 如果没有分配内存失败，释放内存
    {
        free(fs.funcArray_four_key_shift_ctrl_alt);
        fs.funcArray_four_key_shift_ctrl_alt = NULL;
    }
    if (fs.funcArray_four_key_shift_alt_ctrl !=NULL)  // 如果没有分配内存失败，释放内存
    {
        free(fs.funcArray_four_key_shift_alt_ctrl);
        fs.funcArray_four_key_shift_alt_ctrl = NULL;
    }


/************** 三个快捷键 ***************/
    // ctrl
    if (fs.funcArray_three_key_ctrl_alt !=NULL)
    {
        free(fs.funcArray_three_key_ctrl_alt);
        fs.funcArray_three_key_ctrl_alt = NULL;
    }

    if (fs.funcArray_three_key_ctrl_shift !=NULL)
    {
        free(fs.funcArray_three_key_ctrl_shift);
        fs.funcArray_three_key_ctrl_shift = NULL;
    }

    // alt
    if (fs.funcArray_three_key_alt_ctrl !=NULL)
    {
        free(fs.funcArray_three_key_alt_ctrl);
        fs.funcArray_three_key_alt_ctrl = NULL;
    }
    if (fs.funcArray_three_key_alt_shift !=NULL)
    {
        free(fs.funcArray_three_key_alt_shift);
        fs.funcArray_three_key_alt_shift = NULL;
    }

    // shift
    if (fs.funcArray_three_key_shift_ctrl !=NULL)
    {
        free(fs.funcArray_three_key_shift_ctrl);
        fs.funcArray_three_key_shift_ctrl = NULL;
    }
    if (fs.funcArray_three_key_shift_alt !=NULL)
    {
        free(fs.funcArray_three_key_shift_alt);
        fs.funcArray_three_key_shift_alt = NULL;
    }





/////////////////////
    // 两个快捷键
    if (fs.funcArray_two_key_ctrl !=NULL)  // ctrl
    {
        free(fs.funcArray_two_key_ctrl);
        fs.funcArray_two_key_ctrl = NULL;
    }
    if (fs.funcArray_two_key_alt !=NULL)  //alt
    {
        free(fs.funcArray_two_key_alt);
        fs.funcArray_two_key_alt = NULL;
    }

    if (fs.funcArray_two_key_shift !=NULL)  //shift
    {
        free(fs.funcArray_two_key_shift);
        fs.funcArray_two_key_shift = NULL;
    }

///////////////////////////
    // 1快捷键
    if (fs.funcArray_one_key !=NULL)
    {
        free(fs.funcArray_one_key);
        fs.funcArray_one_key = NULL;
    }
}

void cleanup_check() {
    // 释放 Ctrl、Alt、Shift 和 Win 键

    ////// 释放键盘 //////
    int len = sizeof (free_keys.key_code)/sizeof (free_keys.key_code[0]);
    for (int f=0; f<len; f++)
    {
        if (free_keys.key_code[f] !=0)
        {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = free_keys.key_code[f];  // 键位吗码
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
        }
    }

    // 释放鼠标按键
    if (!flag_up.mouse_up)  // 没释放显示false
    {
        if (strcmp(flag_up.mouse_name, "left") ==0)
        {
            INPUT input = {0};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // 假设是左键，根据需要调整
            SendInput(1, &input, sizeof(INPUT));
            flag_up.mouse_up = true; // 更新鼠标抬起标志
        }
        else if (strcmp(flag_up.mouse_name, "right") ==0)
        {
            INPUT input = {0};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; // 假设是左键，根据需要调整
            SendInput(1, &input, sizeof(INPUT));
            flag_up.mouse_up = true; // 更新鼠标抬起标志
        }
        free_funcs();
    }

    // 确保钩子被卸载
    if (hHook)  // 如果没被正确卸载则hHook返回
    {
        // 确保钩子被卸载
        UnhookWindowsHookEx(hHook);       // 卸载钩子
        // 发送程序结束消息
        PostQuitMessage(0);
        freeHotKeys();  // 释放内存
        free_funcs();  // 释放函数数组内存
    }

}

/************* 游戏按键判定 game mode ************/
int ff = 1;
const char *button_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z",  // 26字母
                             "0", "1", "2", "3", "4", "5", "6",
                             "7", "8", "9", "ctrl", "alt", "shift", "enter",
                             "F1", "F2", "F3", "F4", "F5","F6",
                             "F7", "F8", "F9", "F10", "F11", "F12", "space", "esc"};  // 按键列

int button_code_list[] = {65, 66, 67, 68, 69, 70,
                          71, 72, 73, 74, 75, 76,
                          77, 78, 79, 80, 81, 82,
                          83, 84, 85, 86, 87, 88,
                          89, 90, 48, 49, 50, 51,
                          52, 53, 54, 55, 56, 57, VK_CONTROL,
                          VK_MENU, VK_SHIFT, VK_RETURN, VK_F1, VK_F2, VK_F3,
                          VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
                          VK_F11, VK_F12, VK_SPACE, VK_ESCAPE};  // 虚拟键码






bool KeyDownListen(const char *key)
{
    // 获取对应的虚键码
    int button_list_len = sizeof (button_list)/sizeof (button_list[0]);
    int listen_key_code;
    for (int i=0; i<button_list_len; i++)
    {
        if (strcmp(key, button_list[i])==0)  // 查询键与输入的键是否相同，相同做出处理
        {
            listen_key_code = button_code_list[i];
            break;
        }
    }
    // 执行监听
    if (GetAsyncKeyState(listen_key_code) & 0x8000)
    {
        return True;
        // 执行按键按下的操作
    }
}



bool KeyUpListen(const char *key)
{
    bool isPress = False;
    // 获取对应的虚键码
    int button_list_len = sizeof (button_list)/sizeof (button_list[0]);
    int listen_key_code;
    for (int i=0; i<button_list_len; i++)
    {
        if (strcmp(key, button_list[i])==0)  // 查询键与输入的键是否相同，相同做出处理
        {
            listen_key_code = button_code_list[i];
            break;
        }
    }

    // 监听部分
}

/************** 清理部分 ********************/
void ClearHotKey()  // 注销快捷键(自动注销快捷键调用释放内存的函数)
{
    // 确保钩子被卸载
    UnhookWindowsHookEx(hHook);       // 卸载钩子
    // 发送程序结束消息
    PostQuitMessage(0);
    freeHotKeys();  // 释放内存
    cleanup_check();  // 最后检查是否释放所有按键
    free_funcs();  // 释放分配的函数内存
}

// 信号处理函数，用于处理 SIGINT 信号
void handle_sigint(int sig)
{
    (void)sig;  // 避免未使用的警告
}


void ExitCheckWork()  // 检查程序退出后执行的任务
{
    atexit(cleanup_check);  // 退出所执行的任务

    // 设置 SIGINT 信号的处理函数，信号通报
    signal(SIGINT, handle_sigint);
}

int main()
{
    ExitCheckWork();
    KeyDown("c");

    return 0;
}