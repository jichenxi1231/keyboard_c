#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "keyboard_main.h"


void MouseMove(int x, int y)  // 传参允许值为NULL,NULL为空指针
{
    SetCursorPos(x, y);  // 移动鼠标到某处(设置光标位置)
}

/*********************************************************************************/

void MouseClick(int x, int y, int clicks, char button[])  // 传参允许值为NULL,NULL为空指针
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

void GetScreenSIze()
{
    int x_len, y_len;
    x_len=GetSystemMetrics(SM_CXSCREEN);  // 获取x长度
    y_len=GetSystemMetrics(SM_CYSCREEN);  // 获取y长度
    get_scree_size.x = x_len;  // 结构体储存大小(屏幕)
    get_scree_size.y = y_len;  // 结构体储存大小(屏幕)
    printf("Display size x:%d, y:%d\n", get_scree_size.x, get_scree_size.y);
    printf("The resolution is stored in the structure get_scree_size. If necessary, visit get_scree_size.x,get_scree_size.y to get the size\n");
}

/**************************************************************/
void GetMousePosition()  // 获取光标目前所在的坐标
{
    POINT cursorPos;  // 实例化光标结构体，获取位置
    if (GetCursorPos(&cursorPos))
    {
        printf("The current position of the cursor is x:%ld, y:%ld\n", cursorPos.x, cursorPos.y);
        get_mouse_position.x = cursorPos.x;
        get_mouse_position.y = cursorPos.y;
        printf("Cursor coordinates are stored in get_mouse_position. Obtain them yourself\n");
    }
    else
    {
        printf("Sorry, cursor coordinates not found\n");
    }

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
                                   "backspace", "win"};


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
                           VK_RETURN, VK_CAPITAL, VK_CLEAR, VK_BACK, VK_LWIN};

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
        if (shift_up)
        {
            printf("up");
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VK_SHIFT;
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
        }
        else
        {
            printf("");
        }
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

void PasteStr()
{
    // 打开剪切板，NULL 表示当前线程
    if (OpenClipboard(NULL))
    {
        // 从剪切板获取 CF_TEXT 格式的数据句柄
        HANDLE hClipboardData = GetClipboardData(CF_TEXT);

        // 使用 GlobalLock 锁定内存并返回一个指向实际数据的指针
        // 这个指针就是 clipboardText，它指向剪切板中的文本数据
        char* clipboardText = (char*)GlobalLock(hClipboardData);

        // 解锁之前锁定的全局内存
        GlobalUnlock(hClipboardData);

        // 关闭剪切板
        CloseClipboard();
    }
}

