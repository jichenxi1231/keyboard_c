#include "include/keyboard_main.h"
# include <stdio.h>

int main()
{
    CopyStr("比好！！");
    return 0;
}

/*# keyboard库介绍:

### keyboard是一个开源简单的键盘与鼠标操作的库（适用于Windows系统），本库调用了Windowsapi实现了对键盘鼠标的点击操作，函数仿效Python的keyboard库与pyautogui库类似的命名方式，使得函数通俗易懂。
###
###

# keyboard库的功能与函数介绍:

## 1.获取当前屏幕的分辨率（大小）:
### 函数名:GetScreenSIze()  // 用于获取屏幕分辨率，获取到的大小放在结构体get_scree_size中，使用get_scree_size.x, get_scree_size.y即可获取（终端也会打印此信息，下面的函数相同）

## 2.获取鼠标当前的坐标位置:
### GetMousePosition();  // 获取光标目前所在的坐标，获取到的位置放在结构体get_mouse_position中

## 3.将鼠标移动到指定坐标:
### MouseMoveTo(int x, int y);  // x,y坐标; 将鼠标移动到指定的坐标

## 4.鼠标点击函数:
### MouseClick(int x, int y, int clicks, char button[]);  // 鼠标点击函数。 由于本人技术有限需要开发者手动传入所有参数，x，y为坐标，clicks为点击次数，button为鼠标左右键位点击（暂不支持滚轮点击，如果有人用或者有人提议后续会优化与更新加上滚轮点击与滑动）

##  5.快捷键按下:
### PressHotKey(char *key1, char *key2, char *key3);  // 按下快捷键 下面三个参数分别对应快捷键按键，比如ctrl alt s，或者ctrl s NULL（由于我基础薄弱无法实现自由快捷键组合，于是用了特定的逻辑实现了常用的快捷键组合，关于四个乃至更多的快捷键具体看各位与开发者的需求咯）如果两个快捷键组合第三个参数输入NULL即可

## 6.单个按键按下
### PressKey(char *key); // 按键。 快捷键都有了怎么能少了单个按键按下呢，但是由于作者蔡未能实现小键盘那部分区域的按键点击（如果有需求可加QQ号3118556179进行说明）

## 7.输入函数:
### WriteStr(char str_print[], int str_size); // 输入字符窜函数但仅可用英文。 作为一个键鼠操作的库不能进行输入怎么行呢（还是那句话，由于作者蔡，写c语言不足六个月本函数只支持输入英文，与英文的标点，如果有需求请加QQ留意，我一定尽力去找到输入中文的方法）

## 总结:
### 总之由于我第一次写库，并且能力不是很强仅仅实现了一小部分键鼠操作的功能，但是后续我相信我一定能做大做强，若有需要（或许本人也会需要）或许后续会加上注册快捷键的功能与中文输入的功能，并完善快捷键任意点击，键盘任意点击等功能
*/