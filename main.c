#include <stdio.h>
#include "include/keyboard_main.h"
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>


bool start = true;
int i=0;

void run()
{
    i = 0;
    while (start)
    {
        PressHotKey("ctrl", "v", NULL);  // ���¿�ݼ�����
        usleep(50000);
        PressKey("enter");  // ����enter������
        if (!start)
        {
            break;
        }
        i++;
        if (i == 200)
        {
            break;
        }
    }
}

void exit_run()
{
    start = false;
    ClearHotKey();
}

int main()
{
    exit_check_work();  // �˳���⣬�����˳��Զ�����
    CopyStr("����");  // �������ݵ����а�
    AddHotKey("k", NULL, NULL, NULL, exit_run);  // ��ӿ�ݼ�
    AddHotKey("space", NULL, NULL, NULL, run);
    ListenHotKEy();
    return 0;
}
