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
        PressHotKey("ctrl", "v", NULL);  // 按下快捷键复制
        usleep(50000);
        PressKey("enter");  // 按下enter键发送
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
    exit_check_work();  // 退出监测，意外退出自动清理
    CopyStr("测试");  // 复制内容到剪切板
    AddHotKey("k", NULL, NULL, NULL, exit_run);  // 添加快捷键
    AddHotKey("space", NULL, NULL, NULL, run);
    ListenHotKEy();
    return 0;
}
