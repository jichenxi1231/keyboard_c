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
    SetCursorPos(x, y);  // �ƶ���굽ĳ��(���ù��λ��)
}

void MouseDown(char *button)
{
    if (strcmp(button, "left") ==0)
    {
        // ���û������Ĭ�����
        INPUT input = {0};  // ����INPUT�ṹ�������ʾ�����¼���Ϣ
        input.type = INPUT_MOUSE;  // ָ�������¼�����Ϊ����¼�
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;  // �趨����¼�Ϊ�������
        SendInput(1, &input, sizeof(INPUT));  // ʹ��SendInput������������¼�
        // ������걻����
        flag_up.mouse_up = false;  // ��갴��Ϊmouse_up = false
        flag_up.mouse_name = "left";  // ��Ű�����������������û���Ƿ�ͺ��Զ��ͷ�
    }
    else if (strcmp(button, "right") ==0)
    {
        // ���û������Ĭ�����
        INPUT input = {0};  // ����INPUT�ṹ�������ʾ�����¼���Ϣ
        input.type = INPUT_MOUSE;  // ָ�������¼�����Ϊ����¼�
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;  // �趨����¼�Ϊ�������
        SendInput(1, &input, sizeof(INPUT));  // ʹ��SendInput������������¼�
        // ������걻����
        flag_up.mouse_up = false;  // ��갴��Ϊmouse_up = false
        flag_up.mouse_name = "right";  // ��Ű�����������������û���Ƿ�ͺ��Զ��ͷ�
    }
}

void MouseUp(char *button)
{
    if  (strcmp(button, "left") ==0)
    {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // �����������������Ҫ����
        SendInput(1, &input, sizeof(INPUT));
        flag_up.mouse_up = true; // �������̧���־
    }
    else if (strcmp(button, "right")==0)
    {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; // �����������������Ҫ����
        SendInput(1, &input, sizeof(INPUT));
        flag_up.mouse_up = true; // �������̧���־
    }
}

/*********************************************************************************/

void MouseClick(int x, int y, int clicks, char button[])
{
    /* ��clickΪ1ʱ����button��ΪNoneʱִ�е���һ�ε�ָ�� */
    SetCursorPos(x, y);  // �ƶ���굽ĳ��(���ù��λ��)
    if (clicks!=0)
    {
        int click_time = 0;  // ��ʼ���������
        while (click_time <clicks && strcmp(button, "left") ==0)  // ����ʼ�������С��Ŀ����������
        {
            // ���û������Ĭ�����
            INPUT input = {0};  // ����INPUT�ṹ�������ʾ�����¼���Ϣ
            input.type = INPUT_MOUSE;  // ָ�������¼�����Ϊ����¼�
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;  // �趨����¼�Ϊ�������
            SendInput(1, &input, sizeof(INPUT));  // ʹ��SendInput������������¼�
            flag_up.mouse_up = false;  // ��갴��Ϊmouse_up = false
            flag_up.mouse_name = "left";  // ��Ű�����������������û���Ƿ�ͺ��Զ��ͷ�

            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;  // �趨����¼�Ϊ����ͷ�
            SendInput(1, &input, sizeof(INPUT));  // �����ͷ��������¼�
            flag_up.mouse_up = true;  // ��갴��Ϊmouse_up = true;  // �������Ϊtrue
            flag_up.mouse_name = NULL;  // �ͷ�������Ϊ0
            click_time++;
        }

        while (click_time <clicks && strcmp(button, "right") ==0)  // ����ʼ�������С��Ŀ������������
        {
            INPUT input = {0};  // ����INPUT�ṹ�������ʾ�����¼���Ϣ
            input.type = INPUT_MOUSE;  // ָ�������¼�����Ϊ����¼�
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;  // �趨����¼�Ϊ�������
            SendInput(1, &input, sizeof(INPUT));  // ʹ��SendInput������������¼�
            flag_up.mouse_up = false;  // ��갴��Ϊfalse
            flag_up.mouse_name = "right";  // ��갴�£���¼���µİ���


            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;  // �趨����¼�Ϊ�Ҽ��ͷ�
            SendInput(1, &input, sizeof(INPUT));  // �����ͷ�����Ҽ��¼�
            flag_up.mouse_up = true;  // ��갴��Ϊfalse
            flag_up.mouse_name = NULL; // ���º�����Ϊ0
            click_time++;  // ��ʼֵ����
        }
    }
}

ScreenSizeGet GetScreenSIze(bool out_put)
{
    ScreenSizeGet screen_size;
    int x_len, y_len;
    x_len=GetSystemMetrics(SM_CXSCREEN);  // ��ȡx����
    y_len=GetSystemMetrics(SM_CYSCREEN);  // ��ȡy����
    screen_size.x = x_len;  // �ṹ�崢���С(��Ļ)
    screen_size.y = y_len;  // �ṹ�崢���С(��Ļ)
    if (out_put) {
        printf("Display size x:%d, y:%d\n", screen_size.x, screen_size.y);
    }
    return screen_size;
//    If you want to get coordinates you need to instantiate the struct function:
//    ScreenSizeGet screen_size = GetScreenSIze; screen_size.x, screen_size.y
}
/**************************************************************/
MousePositionGet GetMousePosition(bool out_put)  // ��ȡ���Ŀǰ���ڵ�����
{
    POINT cursorPos;  // ʵ�������ṹ�壬��ȡλ��
    if (GetCursorPos(&cursorPos))
    {
        MousePositionGet mouse_position;  // ʵ���ṹ��ȡ���б���
        if (out_put) {
            printf("The current position of the cursor is x:%ld, y:%ld\n", cursorPos.x, cursorPos.y);
        }
        mouse_position.x = cursorPos.x;
        mouse_position.y = cursorPos.y;
        return mouse_position;  // �������ʵ���������꣬�����Ҫ�õ�������Ҫʵ����
        // ��ȡ������Ҫʵ�����ṹ����ͽ�������ֵ�����ڽṹ��ʵ���ı����е������������ṹ���ٻ�ȡ
//        If you want to get coordinates you need to instantiate the struct function:
//        MousePositionGet mouse_position = GetMousePosition(); mouse_position.x,mouse_position.y
    }
    else
    {
        printf("Sorry, cursor coordinates not found\n");
    }

}

// �����ֹ���
void MouseRoll(int move)
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;       // x����
    input.mi.dy = 0;       // y����
    input.mi.mouseData = move; // ��������;���
    input.mi.dwFlags = MOUSEEVENTF_WHEEL; // ���͹����¼�
    input.mi.time = 0;     // ��ǰϵͳʱ��
    input.mi.dwExtraInfo = 0; // ������Ϣ

    SendInput(1, &input, sizeof(INPUT));
}

/******** ���̰��� ********/
void KeyDown(char *key)
{
    // �޸�һ�±�־�����α�־
    /*************************** �����б� ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26��ĸ
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // ������  // ��ĸ�б�


    char *function_keys_list [] = {"ctrl", "alt", "shift", "F1", "F2", "F3", "F4", "F5",
                                   "F6", "F7", "F8", "F9", "F10", "F11", "F12", "esc",
                                   "space", "delete", "tab", "enter", "caps", "clear",
                                   "backspace", "win", "Pause", "page up", "page down", "left arrow",
                                   "right arrow", "down arrow", "up arrow", "insert"};



/****************************������б�********************************/
    int alphabet_code[] = {65, 66, 67, 68, 69, 70,
                           71, 72, 73, 74, 75, 76,
                           77, 78, 79, 80, 81, 82,
                           83, 84, 85, 86, 87, 88,
                           89, 90, 48, 49, 50, 51,  // 48 �Ժ�������
                           52, 53, 54, 55, 56, 57};  // �������

    int function_code[] = {VK_CONTROL, VK_MENU, VK_SHIFT, VK_F1, VK_F2, VK_F3,
                           VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
                           VK_F11, VK_F12, VK_ESCAPE, VK_SPACE, VK_DELETE, VK_TAB,
                           VK_RETURN, VK_CAPITAL, VK_CLEAR, VK_BACK, VK_LWIN, VK_PAUSE,
                           VK_PRIOR, VK_NEXT, VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_INSERT
    };


/****************�б���************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // ��ĸ���ֳ���
    int function_keys_list_len = sizeof (function_keys_list)/sizeof (function_keys_list[0]);  // ���ܼ����鳤��


    for (int i = 0; i<alphabet_list_len; i++)
    {
        // ���������ַ��Ƿ��봫��Ĳ���һ��(�ж���ĸ) �����û������һ��ѭ��
        if (strcmp(key, alphabet_list[i])==0)
        {
            INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

            input.type = INPUT_KEYBOARD; // ָ�� input ������Ϊ��������
            input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
            input.ki.time = 0; // ʱ�����Ϊ 0
            input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0

            // ģ�ⰴ��Ŀ���
            input.ki.wVk = alphabet_code[i]; // ָ��ģ�ⰴ�µļ�Ϊ Ŀ�� ��
            input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
            SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
            flag_up.key_up_1 = false;  // �������̰���
            flag_up.key_name = alphabet_code[i];
            break;
        }
    }

    for (int i=0; i<function_keys_list_len; i++)
    {
        // �Ƿ��봫��Ĳ���һ�� (�жϹ��ܼ�)
        if (strcmp(key, function_keys_list[i])==0)
        {
            INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

            input.type = INPUT_KEYBOARD; // ָ�� input ������Ϊ��������
            input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
            input.ki.time = 0; // ʱ�����Ϊ 0
            input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0

            // ģ�ⰴ��Ŀ���
            input.ki.wVk = function_code[i]; // ָ��ģ�ⰴ�µļ�Ϊ Ŀ�� ��
            input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
            SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
            flag_up.key_up_1 = true;  // һ������
            flag_up.key_name = function_code[i];
            break;
        }
    }
}

//////// �����ͷ� //////////
void KeyUp(char *key)
{
    // �޸�һ�±�־�����α�־
    /*************************** �����б� ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26��ĸ
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // ������  // ��ĸ�б�


    char *function_keys_list [] = {"ctrl", "alt", "shift", "F1", "F2", "F3", "F4", "F5",
                                   "F6", "F7", "F8", "F9", "F10", "F11", "F12", "esc",
                                   "space", "delete", "tab", "enter", "caps", "clear",
                                   "backspace", "win", "Pause", "page up", "page down", "left arrow",
                                   "right arrow", "down arrow", "up arrow", "insert"};



/****************************������б�********************************/
    int alphabet_code[] = {65, 66, 67, 68, 69, 70,
                           71, 72, 73, 74, 75, 76,
                           77, 78, 79, 80, 81, 82,
                           83, 84, 85, 86, 87, 88,
                           89, 90, 48, 49, 50, 51,  // 48 �Ժ�������
                           52, 53, 54, 55, 56, 57};  // �������

    int function_code[] = {VK_CONTROL, VK_MENU, VK_SHIFT, VK_F1, VK_F2, VK_F3,
                           VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
                           VK_F11, VK_F12, VK_ESCAPE, VK_SPACE, VK_DELETE, VK_TAB,
                           VK_RETURN, VK_CAPITAL, VK_CLEAR, VK_BACK, VK_LWIN, VK_PAUSE,
                           VK_PRIOR, VK_NEXT, VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP, VK_INSERT
    };


/****************�б���************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // ��ĸ���ֳ���
    int function_keys_list_len = sizeof (function_keys_list)/sizeof (function_keys_list[0]);  // ���ܼ����鳤��

    for (int i = 0; i<alphabet_list_len; i++) {
        // ���������ַ��Ƿ��봫��Ĳ���һ��(�ж���ĸ) �����û������һ��ѭ��
        if (strcmp(key, alphabet_list[i]) == 0) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = alphabet_code[i];  // ��λ����
            // ���֮ǰ�����������ˣ�������Ҫ�ͷ�
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
            flag_up.key_up_1 = true;  // �������̰���
            flag_up.key_name = 0;
            break;
        }
    }


    for (int i=0; i<function_keys_list_len; i++)
    {
        // �Ƿ��봫��Ĳ���һ�� (�жϹ��ܼ�)
        if (strcmp(key, function_keys_list[i])==0)
        {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = function_code[i];  // ��λ����
            // ���֮ǰ�����������ˣ�������Ҫ�ͷ�
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
            flag_up.key_up_1 = true;  // �������̰���
            flag_up.key_name = 0;
            break;
        }
    }

//    INPUT input = {0};
//    input.type = INPUT_KEYBOARD;
//    input.ki.wVk = vkCode;  // ��λ����
//    // ���֮ǰ�����������ˣ�������Ҫ�ͷ�
//    input.ki.dwFlags = KEYEVENTF_KEYUP;
//    SendInput(1, &input, sizeof(INPUT));
}

void PressHotKey(char *key1, char *key2, char *key3)
{
    // �����ʹ��������ݼ�����None
    // �����ǲ鿴�������飬������������������ƥ������������ð��������Լ�������


    char *button_list[] = {"a", "b", "c", "d", "e", "f", "g",
                           "h", "i", "j", "k", "l", "m",
                           "n", "o", "p", "q", "r", "s",
                           "t", "u", "v", "w", "x", "y", "z"  // 26��ĸ
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // ������


    int button_code_list[] = {65, 66, 67, 68, 69, 70,
                              71, 72, 73, 74, 75, 76,
                              77, 78, 79, 80, 81, 82,
                              83, 84, 85, 86, 87, 88,
                              89, 90, 48, 49, 50, 51,
                              52, 53, 54, 55, 56, 57};  // �������

    int len = sizeof (button_list)/sizeof (button_list[0]);  // �����С


    if (key1 != NULL && key2 != NULL)  // ��������ַ����Ƿ�ΪNone
    {
        if (strcmp(key1, "ctrl") ==0) // �����ݼ���ctrl��ͷ
        {
            for (int i=0; i <len; i++)  // ƥ�䰴���б����봫�������ͬ�İ�������ȡ����������
            {
                // ����ڶ�������������
                if (strcmp(button_list[i], key2) ==0)
                {
                    // ����һ������ṹ�岢��ʼ��
                    INPUT inputs[2] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                    // ��һ������ 'ctrl' ������ṹ��
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'�����������
                    inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                    // �ڶ������� '������ַ�' ������ṹ��
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // '��������'�����������
                    inputs[1].ki.dwFlags = 0; // ��ʾ���°���
                    // �������룬ͬʱ����'ctrl'��'ָ������'��
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = false;  // ���̱�����������ݼ�
                    flag_up.key_ctrl = false;  // ���°���
                    flag_up.key_name = button_code_list[i];  // �������� ctrl+����


                    // ģ�ⰴ���ͷ�
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;  // �����ͷ�������ݼ�
                    flag_up.key_ctrl = true;  // �����ͷ�������ݼ�
                    flag_up.key_name = 0;  // �������Ƹ�Ϊ0
                    break;  // break��ֹѭ���ж�ε����ݼ�
                }

                    // ����ڶ�������alt���� ��ctrl��ͷ
                else if (strcmp(key2, "alt") ==0)
                {
                    if (key3!=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // ����һ������ṹ�岢��ʼ��
                        INPUT inputs[3] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'�����������
                        inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_MENU; // 'alt'�����������
                        inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                        // �ڶ������� '������ַ�' ������ṹ��
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '��������'�����������
                        inputs[2].ki.dwFlags = 0; // ��ʾ���°���
                        // �������룬ͬʱ����'ctrl��"alt',��'ָ������'��
                        SendInput(3, inputs, sizeof(INPUT));  // ����
                        flag_up.key_up_3 = false;  // ������ݼ�
                        flag_up.key_ctrl = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // ��¼��ݼ�

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // ������ݼ��ͷ�
                        flag_up.key_ctrl = true;
                        flag_up.key_alt = true;
                        flag_up.key_name = 0;  // ��ռ�¼�Ŀ�ݼ���ĸ

                        break;
                    }

                }

                    // ����ڶ�������Ϊshift�� ����ctrl��ͷ
                else if (strcmp(key2, "shift") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // ����һ������ṹ�岢��ʼ��
                        INPUT inputs[3] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'�����������
                        inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'�����������
                        inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                        // �ڶ������� '������ַ�' ������ṹ��
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '��������'�����������
                        inputs[2].ki.dwFlags = 0; // ��ʾ���°���
                        // �������룬ͬʱ����'ctrl��"shift',��'ָ������'��
                        SendInput(3, inputs, sizeof(INPUT));  // ����
                        flag_up.key_up_3 = false;  // ������ݼ�
                        flag_up.key_ctrl = false;
                        flag_up.key_shift = false;
                        flag_up.key_name = button_code_list[i];  // ��¼��ݼ�

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // ������ݼ�
                        flag_up.key_ctrl = true;
                        flag_up.key_shift = true;
                        flag_up.key_name = 0;  // ��¼��ݼ�
                        break;
                    }

                }
            }
        }


            // �ж�alt��ͷ
        else if (strcmp(key1, "alt") ==0) // �����ݼ���alt��ͷ
        {
            for (int i=0; i <len; i++)  // ƥ�䰴���б����봫�������ͬ�İ�������ȡ����������
            {
                if (strcmp(button_list[i], key2) ==0)
                {
                    // ����һ������ṹ�岢��ʼ��
                    INPUT inputs[2] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                    // ��һ������ 'alt' ������ṹ��
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_MENU; // 'alt'�����������
                    inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                    // �ڶ������� '������ַ�' ������ṹ��
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // '�������'�����������
                    inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                    // �������룬ͬʱ����'ctrl'��'ָ������'��
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = false;  // ������ݼ�
                    flag_up.key_alt = false;
                    flag_up.key_name = button_code_list[i];


                    // ģ�ⰴ���ͷ�
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;
                    flag_up.key_alt = true;
                    flag_up.key_name = 0;
                    break;
                }

                    // ����ڶ�������Ϊctrl���� ��alt��ͷ
                else if(strcmp(key2, "ctrl") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // ����һ������ṹ�岢��ʼ��
                        INPUT inputs[3] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'�����������
                        inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_MENU; // 'alt'�����������
                        inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                        // �ڶ������� '������ַ�' ������ṹ��
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '��������'�����������
                        inputs[2].ki.dwFlags = 0; // ��ʾ���°���
                        // �������룬ͬʱ����'ctrl��"alt',��'ָ������'��
                        SendInput(3, inputs, sizeof(INPUT));  // ����
                        flag_up.key_up_3 = false;  // ������ݼ�
                        flag_up.key_ctrl = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // ��¼��ݼ�

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // ������ݼ��ͷ�
                        flag_up.key_ctrl = true;
                        flag_up.key_alt = true;
                        flag_up.key_name = 0;  // ��ռ�¼�Ŀ�ݼ���ĸ
                        break;
                    }

                }

                    // ����ڶ���������shift,,��alt��ͷ
                else if (strcmp(key2, "shift") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // ����һ������ṹ�岢��ʼ��
                        INPUT inputs[3] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_MENU; // 'alt'�����������
                        inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'�����������
                        inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                        // �ڶ������� '������ַ�' ������ṹ��
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '��������'�����������
                        inputs[2].ki.dwFlags = 0; // ��ʾ���°���
                        // �������룬ͬʱ����'alt'��"shift',��'ָ������'��
                        SendInput(3, inputs, sizeof(INPUT));  // ����
                        flag_up.key_up_3 = false;  // ������ݼ�
                        flag_up.key_shift = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // ��¼��ݼ�

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // ������ݼ�
                        flag_up.key_shift = true;
                        flag_up.key_alt = true;
                        flag_up.key_name = 0;  // ��¼��ݼ�
                        break;
                    }
                }
            }
        }


            // �ж�shift��ͷ
        else if (strcmp(key1, "shift") ==0) // �����ݼ���shift��ͷ
        {
            for (int i=0; i <len; i++)  // ƥ�䰴���б����봫�������ͬ�İ�������ȡ����������
            {
                if (strcmp(button_list[i], key2) ==0)
                {
                    // ����һ������ṹ�岢��ʼ��
                    INPUT inputs[2] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                    // ��һ������ 'shift' ������ṹ��
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_SHIFT; // 'shift'�����������
                    inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                    // �ڶ������� '������ַ�' ������ṹ��
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // 'B'�����������
                    inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                    // �������룬ͬʱ����'shift'��'ָ������'��
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = false;  // ������ݼ�
                    flag_up.key_shift = false;
                    flag_up.key_name = button_code_list[i];

                    // ģ�ⰴ���ͷ�
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;
                    flag_up.key_shift = true;
                    flag_up.key_name = 0;
                    break;
                }

                    // ����ڶ�������Ϊctrl.������shift��ͷ
                else if (strcmp(key2, "ctrl") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // ����һ������ṹ�岢��ʼ��
                        INPUT inputs[3] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_CONTROL; // 'ctrl'�����������
                        inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'�����������
                        inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                        // �ڶ������� '������ַ�' ������ṹ��
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '��������'�����������
                        inputs[2].ki.dwFlags = 0; // ��ʾ���°���
                        // �������룬ͬʱ����'ctrl��"alt',��'ָ������'��
                        SendInput(3, inputs, sizeof(INPUT));  // ����
                        flag_up.key_up_3 = false;  // ������ݼ�
                        flag_up.key_ctrl = false;
                        flag_up.key_shift = false;
                        flag_up.key_name = button_code_list[i];  // ��¼��ݼ�

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = true;  // ������ݼ�
                        flag_up.key_ctrl = true;
                        flag_up.key_shift = true;
                        flag_up.key_name = 0;  // ��¼��ݼ�
                        break;
                    }
                }

                    // �жϵڶ��������Ƿ���alt,,,��shift��ͷ
                else if(strcmp(key2, "alt") ==0)
                {
                    if (key3 !=NULL && strcmp(button_list[i], key3) ==0)
                    {
                        // ����һ������ṹ�岢��ʼ��
                        INPUT inputs[3] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                        inputs[0].type = INPUT_KEYBOARD;
                        inputs[0].ki.wVk = VK_MENU; // 'alt'�����������
                        inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                        inputs[1].type = INPUT_KEYBOARD;
                        inputs[1].ki.wVk = VK_SHIFT; // 'shift'�����������
                        inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                        // �ڶ������� '������ַ�' ������ṹ��
                        inputs[2].type = INPUT_KEYBOARD;
                        inputs[2].ki.wVk = button_code_list[i]; // '��������'�����������
                        inputs[2].ki.dwFlags = 0; // ��ʾ���°���
                        // �������룬ͬʱ����'alt'��"shift',��'ָ������'��
                        SendInput(3, inputs, sizeof(INPUT));  // ����
                        flag_up.key_up_3 = false;  // ������ݼ�
                        flag_up.key_shift = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = button_code_list[i];  // ��¼��ݼ�

                        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                        SendInput(3, inputs, sizeof(INPUT));
                        flag_up.key_up_3 = false;  // ������ݼ�
                        flag_up.key_shift = false;
                        flag_up.key_alt = false;
                        flag_up.key_name = 0;  // ��¼��ݼ�
                        break;
                    }
                }
            }
        }

            // �����win��
        else if(strcmp(key1, "win") ==0)
        {
            for (int i=0; i<len; i++)
            {
                // ����ڶ�������������
                if (strcmp(button_list[i], key2) ==0)
                {
                    // ����һ������ṹ�岢��ʼ��
                    INPUT inputs[2] = {0};  // [2]��ʾ����Ԫ��ִ���������������{0}��ʼ������
                    // ��һ������ 'win' ������ṹ��
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_LWIN; // 'win'�����������
                    inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                    // �ڶ������� '������ַ�' ������ṹ��
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = button_code_list[i]; // '��������'�����������
                    inputs[1].ki.dwFlags = 0; // ��ʾ���°���

                    // �������룬ͬʱ����'win'��'ָ������'��
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = false;  // ���̰���
                    flag_up.key_win = false;  // Win������
                    flag_up.key_name = button_code_list[i];

                    // ģ�ⰴ���ͷ�
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    SendInput(2, inputs, sizeof(INPUT));
                    flag_up.key_up_2 = true;  // ���̰���
                    flag_up.key_win = true;  // Win������
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
 *          ���汣��             ����BUG
 */



void PressKey(char *key) // ����
{
    /*************************** �����б� ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26��ĸ
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9"};  // ������  // ��ĸ�б�


    char *function_keys_list [] = {"ctrl", "alt", "shift", "F1", "F2", "F3", "F4", "F5",
                                   "F6", "F7", "F8", "F9", "F10", "F11", "F12", "esc",
                                   "space", "delete", "tab", "enter", "caps", "clear",
                                   "backspace", "win", "Pause", "page up", "page down", "left arrow",
                                   "right arrow", "down arrow", "up arrow", "insert"};


    char *symbol_list_not_shift_press[] = {"`", "[", "]", "\\", ";", "''", ",", ".", "/",
                                           "-", "=", "��", "��", "��", "��"};

    char *symbol_list_need_shift_press[] = {"~", "{", "}", "|", ":", "\"\"", "<", ">", "?",
                                            "_", "+","!", "@", "#", "$", "%", "^",
                                            "&", "*", "(",")"};

    char *chinese_symbol_shift_press[] = {"��", "����", "��", "��", "��",
                                          "����", "��" , "��", "����","��","��"};

/****************************������б�********************************/
    int alphabet_code[] = {65, 66, 67, 68, 69, 70,
                           71, 72, 73, 74, 75, 76,
                           77, 78, 79, 80, 81, 82,
                           83, 84, 85, 86, 87, 88,
                           89, 90, 48, 49, 50, 51,  // 48 �Ժ�������
                           52, 53, 54, 55, 56, 57};  // �������

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


/****************�б���************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // ��ĸ���ֳ���
    int symbol_not_shift_len = sizeof (symbol_list_not_shift_press)/sizeof(symbol_list_not_shift_press[0]); // �ַ�����
    int symbol_need_shift_len = sizeof (symbol_list_need_shift_press)/sizeof (symbol_list_need_shift_press[0]); // �ַ����鳤��
    int function_keys_list_len = sizeof (function_keys_list)/sizeof (function_keys_list[0]);  // ���ܼ����鳤��
    int chinese_symbol_shift_press_len = sizeof (chinese_symbol_shift_press)/sizeof (chinese_symbol_shift_press[0]);  // �����ַ������б���


    for (int i = 0; i<alphabet_list_len; i++)
    {
        // ���������ַ��Ƿ��봫��Ĳ���һ��(�ж���ĸ) �����û������һ��ѭ��
        if (strcmp(key, alphabet_list[i])==0)
        {
            INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

            input.type = INPUT_KEYBOARD; // ָ�� input ������Ϊ��������
            input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
            input.ki.time = 0; // ʱ�����Ϊ 0
            input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0

            // ģ�ⰴ��Ŀ���
            input.ki.wVk = alphabet_code[i]; // ָ��ģ�ⰴ�µļ�Ϊ Ŀ�� ��
            input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
            SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
            flag_up.key_up_1 = false;  // ����
            flag_up.key_name = alphabet_code[i];


            // ģ���ͷ�Ŀ���
            input.ki.wVk = alphabet_code[i]; // ָ��ģ���ͷŵļ���Ȼ�� Ŀ�� ��
            input.ki.dwFlags = KEYEVENTF_KEYUP; // ָ�������ͷ��¼���dwFlags ����Ϊ KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // �ٴη��Ͱ����¼���ϵͳ
            flag_up.key_up_1 = true;  // ����
            flag_up.key_name = 0;
            break;
        }
    }

    for (int i=0; i<function_keys_list_len; i++)
    {
        // �Ƿ��봫��Ĳ���һ�� (�жϹ��ܼ�)
        if (strcmp(key, function_keys_list[i])==0)
        {
            INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

            input.type = INPUT_KEYBOARD; // ָ�� input ������Ϊ��������
            input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
            input.ki.time = 0; // ʱ�����Ϊ 0
            input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0

            // ģ�ⰴ��Ŀ���
            input.ki.wVk = function_code[i]; // ָ��ģ�ⰴ�µļ�Ϊ Ŀ�� ��
            input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
            SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
            flag_up.key_up_1 = true;  // һ������
            flag_up.key_name = function_code[i];

            input.ki.wVk = function_code[i]; // ָ��ģ���ͷŵļ���Ȼ�� Ŀ�� ��
            input.ki.dwFlags = KEYEVENTF_KEYUP; // ָ�������ͷ��¼���dwFlags ����Ϊ KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // �ٴη��Ͱ����¼���ϵͳ
            flag_up.key_up_1 = true;
            flag_up.key_name = 0;
            break;
        }
    }

    for (int i=0; i< symbol_not_shift_len; i++)
    {
        // �Ƿ��봫��Ĳ���һ�� (�ж����谴shift�����ķ���)
        if (strcmp(key, symbol_list_not_shift_press[i])==0)
        {
            INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

            input.type = INPUT_KEYBOARD; // ָ�� input ������Ϊ��������
            input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
            input.ki.time = 0; // ʱ�����Ϊ 0
            input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0

            // ģ�ⰴ��Ŀ���
            input.ki.wVk = symbol_not_shift_code[i]; // ָ��ģ�ⰴ�µļ�Ϊ Ŀ�� ��
            input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
            SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
            flag_up.key_up_1 = true;
            flag_up.key_name = symbol_not_shift_code[i];

            input.ki.wVk = symbol_not_shift_code[i]; // ָ��ģ���ͷŵļ���Ȼ�� Ŀ�� ��
            input.ki.dwFlags = KEYEVENTF_KEYUP; // ָ�������ͷ��¼���dwFlags ����Ϊ KEYEVENTF_KEYUP
            SendInput(1, &input, sizeof(INPUT)); // �ٴη��Ͱ����¼���ϵͳ
            flag_up.key_up_1 = false;
            flag_up.key_name = 0;
            break;
        }
    }

    for (int i=0; i<symbol_need_shift_len; i++)
    {
        // ��Ҫ��shift�ķ���
        if (strcmp(key, symbol_list_need_shift_press[i])==0)
        {
            // ������������ṹ�岢��ʼ��
            INPUT inputs[2] = {0};

            // ��һ������ 'shift' ������ṹ��
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_SHIFT; // 'shift'�����������
            inputs[0].ki.dwFlags = 0; // ��ʾ���°���

            // �ڶ������� 'Ŀ�����' ������ṹ��
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = symbol_need_shift_code[i]; // 'Ŀ�����'�����������
            inputs[1].ki.dwFlags = 0; // ��ʾ���°���
            SendInput(2, inputs, sizeof (INPUT));  // ����ָ���shift���������
            flag_up.key_up_2 = false;
            flag_up.key_shift = false;
            flag_up.key_name = symbol_need_shift_code[i];

            inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
            SendInput(2, inputs, sizeof(INPUT));  // ͬʱ�ͷ�
            flag_up.key_up_2 = true;
            flag_up.key_shift = true;
            flag_up.key_name = 0;
            break;
        }
    }

    for (int i=0; i<chinese_symbol_shift_press_len; i++)
    {
        // �����ַ��ж�
        if (strcmp(key, chinese_symbol_shift_press[i])==0)
        {
            // ������������ṹ�岢��ʼ��
            INPUT inputs[2] = {0};

            // ��һ������ 'shift' ������ṹ��
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_SHIFT; // 'shift'�����������
            inputs[0].ki.dwFlags = 0; // ��ʾ���°���

            // �ڶ������� 'Ŀ�����' ������ṹ��
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = chinese_symbol_shift_code[i]; // 'Ŀ�����'�����������
            inputs[1].ki.dwFlags = 0; // ��ʾ���°���
            SendInput(2, inputs, sizeof (INPUT));  // ����ָ���shift���������
            flag_up.key_up_2 = false;
            flag_up.key_shift = false;
            flag_up.key_name = chinese_symbol_shift_code[i];

            inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
            SendInput(2, inputs, sizeof(INPUT));  // ͬʱ�ͷ�
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
    // ����Ӣ���ַ��ܵĺ���
    /*************************** �����б� ***************************/
    char *alphabet_list[] = {"a", "b", "c", "d", "e", "f", "g",
                             "h", "i", "j", "k", "l", "m",
                             "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z"  // 26��ĸ
            ,"0", "1", "2", "3", "4", "5", "6"
            , "7", "8", "9", };  // ������  // ��ĸ�б�



    char *symbol_list_not_shift_press[] = {"`", "[", "]", "\\", ";", "''", ",", ".", "/",
                                           "-", "=", "��", "��", "��", "��"};

    char *symbol_list_need_shift_press[] = {"~", "{", "}", "|", ":", "\"\"", "<", ">", "?",
                                            "_", "+","!", "@", "#", "$", "%", "^",
                                            "&", "*", "(",")"};

/****************************������б�********************************/
    int alphabet_code[] = {65, 66, 67, 68, 69, 70,
                           71, 72, 73, 74, 75, 76,
                           77, 78, 79, 80, 81, 82,
                           83, 84, 85, 86, 87, 88,
                           89, 90, 48, 49, 50, 51,  // 48 �Ժ�������
                           52, 53, 54, 55, 56, 57};  // �������


    int symbol_not_shift_code[] = {VK_OEM_3, VK_OEM_4, VK_OEM_6, VK_OEM_5, VK_OEM_1, VK_OEM_7, 188,
                                   190, VK_OEM_2, VK_OEM_MINUS, VK_OEM_PLUS, 188, 190, VK_OEM_7,
                                   VK_OEM_7};

    int symbol_need_shift_code[] = {VK_OEM_3, VK_OEM_4, VK_OEM_6, VK_OEM_5, VK_OEM_1, VK_OEM_7, 188,
                                    190, VK_OEM_2, VK_OEM_MINUS, VK_OEM_PLUS, 49,
                                    50, 51,52, 53, 54, 55, 56, 57, 48 };


    /****************�б���************************/
    int alphabet_list_len = sizeof (alphabet_list)/sizeof (alphabet_list[0]);  // ��ĸ���ֳ���
    int symbol_not_shift_len = sizeof (symbol_list_not_shift_press)/sizeof(symbol_list_not_shift_press[0]); // �ַ�����
    int symbol_need_shift_len = sizeof (symbol_list_need_shift_press)/sizeof (symbol_list_need_shift_press[0]); // �ַ����鳤��

    /****************************** ִ�в��� ************************************/
    // ѭ�����������ַ����е�ÿһ���ַ�
    for (int i = 0; i < str_size; i++)
    {
        char current_char = str_print[i];  // ���ַ��洢���ַ�����

        // ������ĸ
        for (int alp = 0; alp < alphabet_list_len; alp++)
        {
            // ����Ƿ�ΪСд��ĸ
            if (tolower(current_char) == alphabet_list[alp][0])
            {
                // ����Ƿ�Ϊ��д��ĸ
                bool is_uppercase = isupper(current_char); // ����Ǵ�д

                if (is_uppercase)  // ����д�д��ĸ
                {
                    INPUT inputs[2] = {0};  // ������������
                    // ����Ǵ�д��ĸ��������ģ�ⰴ�� Shift ��
                    inputs[0].type = INPUT_KEYBOARD;
                    inputs[0].ki.wVk = VK_SHIFT; // 'shift'�����������
                    inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                    // ģ�ⰴ��Ŀ���
                    inputs[1].type = INPUT_KEYBOARD;
                    inputs[1].ki.wVk = alphabet_code[alp]; // Ŀ������������
                    inputs[1].ki.dwFlags = 0; // ��ʾ���°���
                    SendInput(2, inputs, sizeof(INPUT));  // ���Ͱ����¼���ϵͳ
                    shift_up = true;  // shift������

                    // �ͷ� Shift ����Ŀ���
                    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                    SendInput(2, inputs, sizeof(INPUT));  // �ٴη��Ͱ����¼���ϵͳ
                    shift_up = false;  // shift���ͷ�
                }
                else
                {
                    // �����Сд��ĸ����ֱ��ģ�ⰴ��Ŀ���
                    INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

                    input.type = INPUT_KEYBOARD;
                    input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
                    input.ki.time = 0; // ʱ�����Ϊ 0
                    input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0

                    // ģ�ⰴ��Ŀ���
                    input.ki.wVk = alphabet_code[alp]; // ָ��ģ�ⰴ�µļ�Ϊ Ŀ�� ��
                    input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
                    SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
                    shift_up = true;  // shift������

                    // ģ���ͷ�Ŀ���
                    input.ki.dwFlags = KEYEVENTF_KEYUP; // ָ�������ͷ��¼���dwFlags ����Ϊ KEYEVENTF_KEYUP
                    SendInput(1, &input, sizeof(INPUT)); // �ٴη��Ͱ����¼���ϵͳ
                    shift_up = false;  // shift���ͷ�
                }
                break;
            }
        }


        for (int syb_no_shift=0; syb_no_shift< symbol_not_shift_len; syb_no_shift++)
        {
            // �Ƿ��봫��Ĳ���һ�� (�ж����谴shift�����ķ���)
            if (current_char == symbol_list_not_shift_press[syb_no_shift][0])  // ȡ����ǰ�ַ����е��ַ������������ַ����бȽ�
            {
                INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

                input.type = INPUT_KEYBOARD; // ָ�� input ������Ϊ��������
                input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
                input.ki.time = 0; // ʱ�����Ϊ 0
                input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0

                // ģ�ⰴ��Ŀ���
                input.ki.wVk = symbol_not_shift_code[syb_no_shift]; // ָ��ģ�ⰴ�µļ�Ϊ Ŀ�� ��
                input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
                SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
                shift_up = true;  // shift������

                input.ki.wVk = symbol_not_shift_code[syb_no_shift]; // ָ��ģ���ͷŵļ���Ȼ�� Ŀ�� ��
                input.ki.dwFlags = KEYEVENTF_KEYUP; // ָ�������ͷ��¼���dwFlags ����Ϊ KEYEVENTF_KEYUP
                SendInput(1, &input, sizeof(INPUT)); // �ٴη��Ͱ����¼���ϵͳ
                shift_up = false;  // shift���ͷ�
                break;
            }
            // ����ո�
            if (current_char == ' ')
            {
                // ģ�ⰴ�¿ո��
                INPUT input; // ����һ�� INPUT �ṹ����� input���������������¼�

                input.type = INPUT_KEYBOARD;
                input.ki.wScan = 0; // ɨ������Ϊ 0��ͨ������Ҫʹ��
                input.ki.time = 0; // ʱ�����Ϊ 0
                input.ki.dwExtraInfo = 0; // ������Ϣ��Ϊ 0


                input.ki.wVk = VK_SPACE; // ָ��ģ�ⰴ�µļ�Ϊ �ո� ��
                input.ki.dwFlags = 0; // ָ�����̰����¼���dwFlags Ϊ 0
                SendInput(1, &input, sizeof(INPUT)); // ���Ͱ����¼���ϵͳ
                shift_up = true;  // shift������

                // ģ���ͷſո��
                input.ki.dwFlags = KEYEVENTF_KEYUP; // ָ�������ͷ��¼���dwFlags ����Ϊ KEYEVENTF_KEYUP
                SendInput(1, &input, sizeof(INPUT)); // �ٴη��Ͱ����¼���ϵͳ
                shift_up = false;  // shift���ͷ�
                break;
            }
        }

        for (int syb_need_shift=0; syb_need_shift< symbol_need_shift_len; syb_need_shift++)
        {
            // �Ƿ��봫��Ĳ���һ�� (�ж��谴shift�����ķ��Ź���)
            if (current_char == symbol_list_need_shift_press[syb_need_shift][0])  // ȡ����ǰ�ַ����е��ַ������������ַ����бȽ�
            {
                // ������������ṹ�岢��ʼ��
                INPUT inputs[2] = {0};

                // ��һ������ 'shift' ������ṹ��
                inputs[0].type = INPUT_KEYBOARD;
                inputs[0].ki.wVk = VK_SHIFT; // 'shift'�����������
                inputs[0].ki.dwFlags = 0; // ��ʾ���°���

                // �ڶ������� 'Ŀ�����' ������ṹ��
                inputs[1].type = INPUT_KEYBOARD;
                inputs[1].ki.wVk = symbol_need_shift_code[syb_need_shift]; // 'Ŀ�����'�����������
                inputs[1].ki.dwFlags = 0; // ��ʾ���°���
                SendInput(2, inputs, sizeof (INPUT));  // ����ָ���shift���������
                shift_up = true;  // shift������

                inputs[0].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                inputs[1].ki.dwFlags = KEYEVENTF_KEYUP; // ��ʾ�����ͷ�
                SendInput(2, inputs, sizeof(INPUT));  // ͬʱ�ͷ�
                shift_up = false;  // shift���ͷ�
                break;
            }
        }
    }
    if (!shift_up)
    {
        // ����INPUT�ṹ��
        INPUT input_shift = {0};
        input_shift.type = INPUT_KEYBOARD;  // ָ����������Ϊ����

        // ģ���ͷ�Shift��
        input_shift.ki.wVk = VK_SHIFT;       // �����������ΪShift
        input_shift.ki.dwFlags = KEYEVENTF_KEYUP;  // ָ�������ͷ��¼�

        // ���ͼ����ͷ��¼�
        SendInput(1, &input_shift, sizeof(INPUT));
    }
}

void copy_str_in(copy_str_structs self)  // ���Ƶ����а�ĺ���������������CopyStr������
{
    if (OpenClipboard(NULL))
    {
        // ��ռ��а�����
        EmptyClipboard();

        // �����ڴ沢���ı����ݸ��Ƶ�ȫ���ڴ��
        HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, strlen(self.textToCopy) + 1); // +1��Ϊ�˰����ַ����Ľ�β null �ַ�
        if (hglbCopy != NULL) {
            LPVOID lpCopy = GlobalLock(hglbCopy);
            strcpy((char*)lpCopy, self.textToCopy);
            GlobalUnlock(hglbCopy);

            // ��ȫ���ڴ������Ϊ���а�����
            SetClipboardData(CF_TEXT, hglbCopy);
        }

        // �رռ��а�
        CloseClipboard();
    }
}

void CopyStr(const char *str)   // �����ַ��ܵ����а�
{  // �����ַ��ܵ����а�
    copy_str_structs self = {str, copy_str_in};
    self.copy_str_in(self);
}

typedef struct {
    char* text; // ָ��������ı���ָ��
    size_t length; // �ı�����
} ClipboardText;

PasteStrStructs PasteStr()
{
//    PasteStrStructs str = PasteStr();  // ʹ�÷���
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
        result.text[0] = '\0'; // ����޷���ȡ�ı�������Ϊ���ַ���
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

/************** ��ݼ�ע�� ***********************/

// ����ȫ�ֱ��������湳�Ӿ��
HHOOK hHook = NULL;      // HHOOK �������ڱ��湳�Ӿ��

HotKeyList *head = NULL;  // �б�ͷָ��


// ���̹��ӵĻص�����
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    char *button_list[] = {"a", "b", "c", "d", "e", "f", "g",
                           "h", "i", "j", "k", "l", "m",
                           "n", "o", "p", "q", "r", "s",
                           "t", "u", "v", "w", "x", "y", "z",  // 26��ĸ
                           "0", "1", "2", "3", "4", "5", "6",
                           "7", "8", "9", "ctrl", "alt", "shift", "enter",
                           "F1", "F2", "F3", "F4", "F5","F6",
                           "F7", "F8", "F9", "F10", "F11", "F12", "space", "esc"};  // ������

    int button_code_list[] = {65, 66, 67, 68, 69, 70,
                              71, 72, 73, 74, 75, 76,
                              77, 78, 79, 80, 81, 82,
                              83, 84, 85, 86, 87, 88,
                              89, 90, 48, 49, 50, 51,
                              52, 53, 54, 55, 56, 57, VK_CONTROL,
                              VK_MENU, VK_SHIFT, VK_RETURN, VK_F1, VK_F2, VK_F3,
                              VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
                              VK_F11, VK_F12, VK_SPACE, VK_ESCAPE};  // �������

    int button_list_len = sizeof(button_list) / sizeof(button_list[0]);  // �����б���
    int key1_code, key2_code, key3_code, key4_code;  // �����ĸ���ݼ�����



    // ������ݼ�����*current = head����б�ͷָ�벻ΪNULLʱ���ֵ�ͷ���ָ����һ��ʵ�����Լ�
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

            // ��鹳�Ӳ����Ƿ�ɹ�
            if (nCode >= 0)
            {
                // ��ȡ���̹��ӽṹ��
                PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                // ����Ƿ�Ϊ���̰�����Ϣ����ͬʱ����ע��Ŀ�ݼ�
                if (wParam == WM_KEYDOWN &&
                    GetAsyncKeyState(key1_code) & 0x8000 &&  // ���key1�������Ƿ���
                    GetAsyncKeyState(key2_code) & 0x8000 &&  // ���key2�������Ƿ���
                    GetAsyncKeyState(key3_code) & 0x8000 &&  // ���key3�������Ƿ���
                    pKey->vkCode == key4_code)                // �����ĸ����Ƿ���
                {
                    // ִ����Ӧ�ĺ���
                    current->data.function();
                    break;
                }
            }
        }

            // �����ݼ�ֻ������
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

            // ��鹳�Ӳ����Ƿ�ɹ�
            if (nCode >= 0)
            {
                // ��ȡ���̹��ӽṹ��
                PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                // ����Ƿ�Ϊ���̰�����Ϣ����ͬʱ����ע��Ŀ�ݼ�
                if (wParam == WM_KEYDOWN &&
                    GetAsyncKeyState(key1_code) & 0x8000 &&  // ���key1�������Ƿ���
                    GetAsyncKeyState(key2_code) & 0x8000 &&  // ���key2�������Ƿ���
                    pKey->vkCode == key3_code)                // �����������Ƿ���
                {
                    // ִ����Ӧ�ĺ���
                    current->data.function();
                    break;
                }
            }
        }

            // ���ֻע��������ݼ�
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

                // ��鹳�Ӳ����Ƿ�ɹ�
                if (nCode >= 0)
                {
                    // ��ȡ���̹��ӽṹ��
                    PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                    // ����Ƿ�Ϊ���̰�����Ϣ����ͬʱ����ע��Ŀ�ݼ�
                    if (wParam == WM_KEYDOWN &&
                        GetAsyncKeyState(key1_code) & 0x8000 &&  // ���key1�������Ƿ���
                        pKey->vkCode == key2_code)                // �����������Ƿ���
                    {
                        // ִ����Ӧ�ĺ���
                        current->data.function();
                        break;
                    }
                }
            }
        }

            // ֻ����һ����ݼ�
            // ���ֻע��������ݼ�
        else if (current->data.key1 != NULL && current->data.key2 == NULL && current->data.key3 == NULL && current->data.key4 == NULL)
        {
            for (int i = 0; i < button_list_len; i++)
            {
                if (strcmp(current->data.key1, button_list[i]) == 0)
                {
                    key1_code = button_code_list[i];
                }
                // ��鹳�Ӳ����Ƿ�ɹ�
                if (nCode >= 0)
                {
                    // ��ȡ���̹��ӽṹ��
                    PKBDLLHOOKSTRUCT pKey = (PKBDLLHOOKSTRUCT)lParam;

                    if (wParam == WM_KEYDOWN &&
                        pKey->vkCode == key1_code)                // �����������Ƿ���
                    {
                        // ִ����Ӧ�ĺ���
                        current->data.function();
                        break;
                    }
                }
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// ��ӿ�ݼ��ĺ���
void AddHotKey(char *key1, char *key2, char *key3, char *key4, void (*target_void_func)())
{
    HotKeyList *newNode = (HotKeyList *)malloc(sizeof(HotKeyList));  // �����ڴ�
    newNode->data.key1 = key1;  // ���ÿ�ݼ�
    newNode->data.key2 = key2;
    newNode->data.key3 = key3;
    newNode->data.key4 = key4;
    newNode->data.function = target_void_func;  // ���ûص�����

    // newNode->next = head; �� head = newNode; ���������´����Ľڵ� newNode ���뵽�����е�ͷ���������������ͷ��ָ�롣
    newNode->next = head;  // ������������,���½ڵ�� next ָ��ָ��ǰ�����ͷ���ڵ��ԭ�������ͷ���ڵ㽫��Ϊ�ڶ����ڵ㡣
    head = newNode;  // ����ͷָ��,ͨ���� head ����Ϊ newNode���½ڵ��Ϊ���������ͷ����Ҳ��������ĵ�һ��Ԫ��
    // ʾ��:node1 -> node2 -> NULL
}

void freeHotKeys()
{
    HotKeyList *current = head;
    HotKeyList *temp;

    // ���������ͷ�ÿ���ڵ���ڴ�
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);  // �ͷŵ�ǰ�ڵ���ڴ�
    }

    head = NULL;  // ���ͷ��ָ��
}

// ע��һ�����̵ͼ�����
void ListenHotKEy()
{
    // ������ݼ�ѭ������
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);  // ��װ�ͼ����̹���

    MSG msg;          // MSG �ṹ�����ڴ洢����Ϣ�����л�ȡ����Ϣ


    // ������Ϣѭ��
    while (GetMessage(&msg, NULL, 0, 0))  // ����Ϣ�����л�ȡ��Ϣ
    {
        TranslateMessage(&msg);           // ���������ת�����ַ�
        DispatchMessage(&msg);            // �ַ���Ϣ�����ڹ���
    }

}
//// ����������ڳ������ǰ������
void ReleaseKey(WORD vkCode, bool *keyUpFlag)
{
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vkCode;  // ��λ����
    if (!*keyUpFlag)  // ��������½ṹ�巵��true��֮����False
    {
        printf("ok");
        // ���֮ǰ�����������ˣ�������Ҫ�ͷ�
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
        *keyUpFlag = true; // ���±�־����ʾ�������ͷ�
        printf("%d", vkCode);
    }
}

void cleanup_check() {
    // �ͷ� Ctrl��Alt��Shift �� Win ��
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

    // �ͷ����һ�����µļ�
    if (flag_up.key_name != 0)
    {
        ReleaseKey((WORD)flag_up.key_name, &flag_up.key_up_1);
    }

    // �ͷ���갴��
    if (!flag_up.mouse_up)  // û�ͷ���ʾfalse
    {
        if (strcmp(flag_up.mouse_name, "left") ==0)
        {
            INPUT input = {0};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // �����������������Ҫ����
            SendInput(1, &input, sizeof(INPUT));
            flag_up.mouse_up = true; // �������̧���־
        }
        else if (strcmp(flag_up.mouse_name, "right") ==0)
        {
            INPUT input = {0};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; // �����������������Ҫ����
            SendInput(1, &input, sizeof(INPUT));
            flag_up.mouse_up = true; // �������̧���־
        }
    }

    // ȷ�����ӱ�ж��
    if (!hHook)
    {
        // ȷ�����ӱ�ж��
        UnhookWindowsHookEx(hHook);       // ж�ع���
        // ���ͳ��������Ϣ
        PostQuitMessage(0);
        freeHotKeys();  // �ͷ��ڴ�
    }

}

/************** ������ ********************/
void ClearHotKey()  // ע����ݼ�(�Զ�ע����ݼ������ͷ��ڴ�ĺ���)
{
    // ȷ�����ӱ�ж��
    UnhookWindowsHookEx(hHook);       // ж�ع���
    // ���ͳ��������Ϣ
    PostQuitMessage(0);
    freeHotKeys();  // �ͷ��ڴ�
    cleanup_check();  // ������Ƿ��ͷ����а���
}

// �źŴ����������ڴ��� SIGINT �ź�
void handle_sigint(int sig)
{
    (void)sig;  // ����δʹ�õľ���
}


void exit_check_work()  // �������˳���ִ�е�����
{
    atexit(cleanup_check);  // �˳���ִ�е�����

    // ���� SIGINT �źŵĴ��������ź�ͨ��
    signal(SIGINT, handle_sigint);
}


