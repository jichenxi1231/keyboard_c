#include <stdio.h>
#include "include/keyboard_main.h"
#include <stdbool.h>
#include <pthread.h>

int main()
{
    MousePositionGet position =  GetMousePosition(false);  // 获取鼠标当前坐标并输出
    printf("%ld:x, %ld:y", position.x, position.y);

//    ScreenSizeGet screen =  GetScreenSIze(0);  // 输出坐标内容
//    printf("%d:x, %d:y", screen.x, screen.y);

//    AddHotKey("ctrl", "l", NULL, NULL, ClearHotKey);  // 注册快捷键，第五个参数为回调函数
//    AddHotKey("esc", NULL, NULL, NULL, ClearHotKey);  // 可注册多个快捷键
//    ListenHotKEy();  // 监听快捷键  ClearHotKey在程序结束时必须调用用它来注销快捷键注册，比如ClearHotKey()

//    PasteStrStructs str = PasteStr();  // 获取字符窜存入结构体
//    printf("%s", str.text);  // 输出字符窜
//    FreePasteStr(&str);  // 释放内存
    return 0;
}