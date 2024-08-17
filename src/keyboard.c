#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "keyboard_main.h"
#include <unistd.h> // For sleep()
#include <signal.h> // For signal()


void MouseMoveTo(int x, int y)
{
    SetCursorPos(x, y);  // 移动鼠标到某处(设置光标位置)
}

void MouseDown(char *button)
{
    if (strcmp(button, "left") ==0)
    {
        // 如果没传参数默认左键
        INPUT input = {0};  // 定义INPUT结构体变量表示输入事件信息
        input.type = INPUT_MOUSE;  // 指定输入事件类型为鼠标事件
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;  // 设定鼠标事件为左键按下
        SendInput(1, &input, sizeof(INPUT));  // 使用SendInput函数发送鼠标事件
        // 设置鼠标被按下
        flag_up.mouse_up = false;  // 鼠标按下为mouse_up = false
        flag_up.mouse_name = "left";  // 存放按键名称如果程序结束没有是否就好自动释放
    }
    else if (strcmp(button, "right") ==0)
    {
        // 如果没传参数默认左键
        INPUT input = {0};  // 定义INPUT结构体变量表示输入事件信息
        input.type = INPUT_MOUSE;  // 指定输入事件类型为鼠标事件
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;  // 设定鼠标事件为左键按下
        SendInput(1, &input, sizeof(INPUT));  // 使用SendInput函数发送鼠标事件
        // 设置鼠标被按下
        flag_up.mouse_up = false;  // 鼠标按下为mouse_up = false
        flag_up.mouse_name = "right";  // 存放按键名称如果程序结束没有是否就好自动释放
    }
}

void MouseUp(char *button)
{
    if  (strcmp(button, "left") ==0)
    {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // 假设是左键，根据需要调整
        SendInput(1, &input, sizeof(INPUT));
        flag_up.mouse_up = true; // 更新鼠标抬起标志
    }
    else if (strcmp(button, "right")==0)
    {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; // 假设是左键，根据需要调整
        SendInput(1, &input, sizeof(INPUT));
        flag_up.mouse_up = true; // 更新鼠标抬起标志
    }
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
            flag_up.mouse_up = false;  // 鼠标按下为mouse_up = false
            flag_up.mouse_name = "left";  // 存放按键名称如果程序结束没有是否就好自动释放

            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;  // 设定鼠标事件为左键释放
            SendInput(1, &input, sizeof(INPUT));  // 发送释放鼠标左键事件
            flag_up.mouse_up = true;  // 鼠标按下为mouse_up = true;  // 鼠标升起为true
            flag_up.mouse_name = NULL;  // 释放了设置为0
            click_time++;
        }

        while (click_time <clicks && strcmp(button, "right") ==0)  // 当初始点击次数小于目标点击次数增加
        {
            INPUT input = {0};  // 定义INPUT结构体变量表示输入事件信息
            input.type = INPUT_MOUSE;  // 指定输入事件类型为鼠标事件
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;  // 设定鼠标事件为左键按下
            SendInput(1, &input, sizeof(INPUT));  // 使用SendInput函数发送鼠标事件
            flag_up.mouse_up = false;  // 鼠标按下为false
            flag_up.mouse_name = "right";  // 鼠标按下，记录按下的按键


            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;  // 设定鼠标事件为右键释放
            SendInput(1, &input, sizeof(INPUT));  // 发送释放鼠标右键事件
            flag_up.mouse_up = true;  // 鼠标按下为false
            flag_up.mouse_name = NULL; // 按下后设置为0
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

/******** 键盘按下 ********/
void KeyDown(char *key)
{
    // 修改一下标志，传参标志
    /*************************** 按键列表 ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26字母
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // 按键列  // 字母列表


    char *function_keys_list [] = {"ctrl", "alt", "shift", "F1", "F2", "F3", "F4", "F5",
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
            flag_up.key_up_1 = false;  // 单键键盘按下
            flag_up.key_name = alphabet_code[i];
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
            flag_up.key_up_1 = true;  // 一个按键
            flag_up.key_name = function_code[i];
            break;
        }
    }
}

//////// 键盘释放 //////////
void KeyUp(char *key)
{
    // 修改一下标志，传参标志
    /*************************** 按键列表 ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26字母
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // 按键列  // 字母列表


    char *function_keys_list [] = {"ctrl", "alt", "shift", "F1", "F2", "F3", "F4", "F5",
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
            flag_up.key_up_1 = true;  // 单键键盘按下
            flag_up.key_name = 0;
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
            flag_up.key_up_1 = true;  // 单键键盘按下
            flag_up.key_name = 0;
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

void PressHotKey(char *key1, char *key2, char *key3)
{
    // 如果不使用其他快捷键输入None
    // 这里是查看两个数组，如果参数传入的与数组匹配就索引数组获得按键名称以及索引码


    char *button_list[] = {"a", "b", "c", "d", "e", "f", "g",
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
                    flag_up.key_up_2 = false;  // 键盘被按下两个快捷键
                    flag_up.key_ctrl = false;  // 按下按键
                    flag_up.key_name = button_code_list[i];  // 按键名称 ctrl+名字


                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;  // 键盘释放两个快捷键
                    flag_up.key_ctrl = true;  // 键盘释放两个快捷键
                    flag_up.key_name = 0;  // 按键名称改为0
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
                        flag_up.key_up_3 = false;  // 三个快捷键
                        flag_up.key_ctrl = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // 记录快捷键

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // 三个快捷键释放
                        flag_up.key_ctrl = true;
                        flag_up.key_alt = true;
                        flag_up.key_name = 0;  // 清空记录的快捷键字母

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
                        flag_up.key_up_3 = false;  // 三个快捷键
                        flag_up.key_ctrl = false;
                        flag_up.key_shift = false;
                        flag_up.key_name = button_code_list[i];  // 记录快捷键

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // 三个快捷键
                        flag_up.key_ctrl = true;
                        flag_up.key_shift = true;
                        flag_up.key_name = 0;  // 记录快捷键
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
                    flag_up.key_up_2 = false;  // 两个快捷键
                    flag_up.key_alt = false;
                    flag_up.key_name = button_code_list[i];


                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;
                    flag_up.key_alt = true;
                    flag_up.key_name = 0;
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
                        flag_up.key_up_3 = false;  // 三个快捷键
                        flag_up.key_ctrl = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // 记录快捷键

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // 三个快捷键释放
                        flag_up.key_ctrl = true;
                        flag_up.key_alt = true;
                        flag_up.key_name = 0;  // 清空记录的快捷键字母
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
                        flag_up.key_up_3 = false;  // 三个快捷键
                        flag_up.key_shift = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // 记录快捷键

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // 三个快捷键
                        flag_up.key_shift = true;
                        flag_up.key_alt = true;
                        flag_up.key_name = 0;  // 记录快捷键
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
                    flag_up.key_up_2 = false;  // 两个快捷键
                    flag_up.key_shift = false;
                    flag_up.key_name = button_code_list[i];

                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;
                    flag_up.key_shift = true;
                    flag_up.key_name = 0;
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
                        flag_up.key_up_3 = false;  // 三个快捷键
                        flag_up.key_ctrl = false;
                        flag_up.key_shift = false;
                        flag_up.key_name = button_code_list[i];  // 记录快捷键

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // 三个快捷键
                        flag_up.key_ctrl = true;
                        flag_up.key_shift = true;
                        flag_up.key_name = 0;  // 记录快捷键
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
                        flag_up.key_up_3 = false;  // 三个快捷键
                        flag_up.key_shift = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // 记录快捷键

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = false;  // 三个快捷键
                        flag_up.key_shift = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = 0;  // 记录快捷键
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
                    flag_up.key_up_2 = false;  // 键盘按下
                    flag_up.key_win = false;  // Win键按下
                    flag_up.key_name = button_code_list[i];

                    // 模拟按键释放
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;  // 键盘按下
                    flag_up.key_win = true;  // Win键按下
                    flag_up.key_name = 0;
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



void PressKey(char *key) // 按键
{
    /*************************** 按键列表 ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26字母
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // 按键列  // 字母列表


    char *function_keys_list [] = {"ctrl", "alt", "shift", "F1", "F2", "F3", "F4", "F5",
                                   "F6", "F7", "F8", "F9", "F10", "F11", "F12", "esc",
                                   "space", "delete", "tab", "enter", "caps", "clear",
                                   "backspace", "win", "Pause", "page up", "page down", "left arrow",
                                   "right arrow", "down arrow", "up arrow", "insert"};


    char *symbol_list_not_shift_press[] = {"`", "[", "]", "\\", ";", "''", ",", ".", "/",
                                           "-", "=", "，", "。", "’", "‘"};

    char *symbol_list_need_shift_press[] = {"~", "{", "}", "|", ":", "\"\"", "<", ">", "?",
                                            "_", "+","!", "@", "#", "$", "%", "^",
                                            "&", "*", "(",")"};

    char *chinese_symbol_shift_press[] = {"：", "“”", "《", "》", "？",
                                          "——", "！" , "￥", "……","（","）"};

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
            flag_up.key_up_1 = false;  // 单键
            flag_up.key_name = alphabet_code[i];


            // 模拟释放目标键
            input.ki.wVk = alphabet_code[i]; // 指定模拟释放的键仍然是 目标 键
            input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
            flag_up.key_up_1 = true;  // 单键
            flag_up.key_name = 0;
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
            flag_up.key_up_1 = true;  // 一个按键
            flag_up.key_name = function_code[i];

            input.ki.wVk = function_code[i]; // 指定模拟释放的键仍然是 目标 键
            input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
            flag_up.key_up_1 = true;
            flag_up.key_name = 0;
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
            flag_up.key_up_1 = true;
            flag_up.key_name = symbol_not_shift_code[i];

            input.ki.wVk = symbol_not_shift_code[i]; // 指定模拟释放的键仍然是 目标 键
            input.ki.dwFlags = KEYEVENTF_KEYUP; // 指定键盘释放事件，dwFlags 设置为 KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // 再次发送按键事件给系统
            flag_up.key_up_1 = false;
            flag_up.key_name = 0;
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
            flag_up.key_up_2 = false;
            flag_up.key_shift = false;
            flag_up.key_name = symbol_need_shift_code[i];

            inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            SendInput(2, inputs, sizeof(INPUT));  // 同时释放
            flag_up.key_up_2 = true;
            flag_up.key_shift = true;
            flag_up.key_name = 0;
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
            flag_up.key_up_2 = false;
            flag_up.key_shift = false;
            flag_up.key_name = chinese_symbol_shift_code[i];

            inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // 表示按键释放
            SendInput(2, inputs, sizeof(INPUT));  // 同时释放
            flag_up.key_up_2 = true;
            flag_up.key_shift = true;
            flag_up.key_name = 0;
            break;
        }
    }

}


void WriteStr(const char str_print[], int str_size)
{
    bool shift_up = false;
    // 输入英文字符窜的函数
    /*************************** 按键列表 ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26字母
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9", };  // 按键列  // 字母列表



    char *symbol_list_not_shift_press[] = {"`", "[", "]", "\\", ";", "''", ",", ".", "/",
                                           "-", "=", "，", "。", "’", "‘"};

    char *symbol_list_need_shift_press[] = {"~", "{", "}", "|", ":", "\"\"", "<", ">", "?",
                                            "_", "+","!", "@", "#", "$", "%", "^",
                                            "&", "*", "(",")"};

/****************************虚键码列表********************************/
    int alphabet_code[] = {65, 66, 67, 68, 69, 70,
                           71, 72, 73, 74, 75, 76,
                           77, 78, 79, 80, 81, 82,
                           83, 84, 85, 86, 87, 88,
                           89, 90, 48, 49, 50, 51,  // 48 以后是数组
                           52, 53, 54, 55, 56, 57};  // 虚拟键码


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
//    PasteStrStructs str = PasteStr();  // 使用方法
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
HHOOK hHook = NULL;      // HHOOK 类型用于保存钩子句柄

HotKeyList *head = NULL;  // 列表头指针


// 键盘钩子的回调函数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    char *button_list[] = {"a", "b", "c", "d", "e", "f", "g",
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
        if (current ->data.key1!=NULL && current ->data.key2!=NULL && current ->data.key3!=NULL && current ->data.key4!=NULL)
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
                if (wParam == WM_KEYDOWN &&
                    GetAsyncKeyState(key1_code) & 0x8000 &&  // 检查key1参数键是否按下
                    GetAsyncKeyState(key2_code) & 0x8000 &&  // 检查key2参数键是否按下
                    GetAsyncKeyState(key3_code) & 0x8000 &&  // 检查key3参数键是否按下
                    pKey->vkCode == key4_code)                // 检查第四个键是否按下
                {
                    // 执行相应的函数
                    current->data.function();
                    break;
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
                if (wParam == WM_KEYDOWN &&
                    GetAsyncKeyState(key1_code) & 0x8000 &&  // 检查key1参数键是否按下
                    GetAsyncKeyState(key2_code) & 0x8000 &&  // 检查key2参数键是否按下
                    pKey->vkCode == key3_code)                // 检查第三个键是否按下
                {
                    // 执行相应的函数
                    current->data.function();
                    break;
                }
            }
        }

            // 如果只注册两个快捷键
        else if (current->data.key1 != NULL && current->data.key2 != NULL && current->data.key3 == NULL && current->data.key4 == NULL)
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

                // 检查钩子操作是否成功
                if (nCode >= 0)
                {
                    // 获取键盘钩子结构体
                    PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                    // 检查是否为键盘按下消息，且同时按下注册的快捷键
                    if (wParam == WM_KEYDOWN &&
                        GetAsyncKeyState(key1_code) & 0x8000 &&  // 检查key1参数键是否按下
                        pKey->vkCode == key2_code)                // 检查第三个键是否按下
                    {
                        // 执行相应的函数
                        current->data.function();
                        break;
                    }
                }
            }
        }

            // 只按下一个快捷键
            // 如果只注册两个快捷键
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
                        pKey->vkCode == key1_code)                // 检查第三个键是否按下
                    {
                        // 执行相应的函数
                        current->data.function();
                        break;
                    }
                }
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// 添加快捷键的函数
void AddHotKey(char *key1, char *key2, char *key3, char *key4, void (*target_void_func)())
{
    HotKeyList *newNode = (HotKeyList *)malloc(sizeof(HotKeyList));  // 分配内存
    newNode->data.key1 = key1;  // 设置快捷键
    newNode->data.key2 = key2;
    newNode->data.key3 = key3;
    newNode->data.key4 = key4;
    newNode->data.function = target_void_func;  // 设置回调函数

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
//// 这个函数将在程序结束前被调用
void ReleaseKey(WORD vkCode, bool *keyUpFlag)
{
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vkCode;  // 键位吗码
    if (!*keyUpFlag)  // 如果被按下结构体返回true反之返回False
    {
        printf("ok");
        // 如果之前按键被按下了，现在需要释放
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
        *keyUpFlag = true; // 更新标志，表示按键已释放
        printf("%d", vkCode);
    }
}

void cleanup_check() {
    // 释放 Ctrl、Alt、Shift 和 Win 键
    if (flag_up.key_ctrl)
    {
        ReleaseKey(VK_CONTROL, &flag_up.key_ctrl);
    }
    else if (flag_up.key_alt)
    {
        ReleaseKey(VK_MENU, &flag_up.key_alt);
    }
    else if (flag_up.key_shift)
    {
        ReleaseKey(VK_SHIFT, &flag_up.key_shift);
    }
    if (flag_up.key_win)
    {
        ReleaseKey(VK_LWIN, &flag_up.key_win);
    }

    // 释放最后一个按下的键
    if (flag_up.key_name != 0)
    {
        ReleaseKey((WORD)flag_up.key_name, &flag_up.key_up_1);
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
    }

    // 确保钩子被卸载
    if (!hHook)
    {
        // 确保钩子被卸载
        UnhookWindowsHookEx(hHook);       // 卸载钩子
        // 发送程序结束消息
        PostQuitMessage(0);
        freeHotKeys();  // 释放内存
    }

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
}

// 信号处理函数，用于处理 SIGINT 信号
void handle_sigint(int sig)
{
    (void)sig;  // 避免未使用的警告
}


void exit_check_work()  // 检查程序退出后执行的任务
{
    atexit(cleanup_check);  // 退出所执行的任务

    // 设置 SIGINT 信号的处理函数，信号通报
    signal(SIGINT, handle_sigint);
}


