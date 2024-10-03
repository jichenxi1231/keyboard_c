#include <stdio.h>
#include "include/keyboard_main.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#define True 1
#define False 0

bool run = true;



int main()
{
    ExitCheckWork();
    KeyDown("a");
    int a;
    printf("ÊäÈë:");
    scanf("%d", &a);
    if (a>0)
    {
        KeyUp("a");
    }
    else
    {
        KeyDown("v");

    }
    return 0;
}