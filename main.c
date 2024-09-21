#include <stdio.h>
#include "include/keyboard_main.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#define True 1
#define False 0

bool run = true;

int i = 0;
int end = 1000;
pthread_t T1;


void *start_run(void *argc)
{
    const char *lists[] = {"稍微", "有那么一点点", "卡.....", "呃", "我擦！"};
    while (run)
    {
        for (i; i < 4; i++)
        {
            CopyStr(lists[i]);
            usleep(5000);
            PressHotKey("ctrl", "v", NULL);
            usleep(5000);
            PressKey("enter");
            if (!run) {
                break;
            }
        }
        i = 0;
    }
}

void start_send_t()
{
    pthread_create(&T1, NULL, start_run, NULL);
}

void end_run()
{
    run = false;
    ClearHotKey();
}



int main()
{
    exit_check_work();
    AddHotKey("space", NULL, NULL, NULL, start_send_t);
    AddHotKey("1", NULL, NULL, NULL, end_run);
    ListenHotKEy();
    KeyUp("ctrl");
    KeyUp("v");
    KeyUp("enter");
    printf("break\n");
    return 0;
}