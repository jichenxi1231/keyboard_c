# 库的介绍:
## 这是一个关于语言的键鼠操作库，适用于Windows，但是后续会努力更新使得其兼容cpp，也麻烦各位cpp的大佬们进行测试

# 库的用途: 
## 本库基于Python的keyboard与pyautogui这两个库模仿写出了keyboard有关于c的键鼠操作库其主要优势就是简单方便与好用
# 库的使用:(函数介绍)

## 1.鼠标移动(用于鼠标移动到指定坐标)
### void MouseMoveTo(int x, int y);  // x,y坐标;

## 2.鼠标点击
### void MouseClick(int x, int y, int clicks, char button[]);  // 鼠标点击函数

## 3.鼠标按下
### void MouseDown(char *button);  // 鼠标按下键位

## 4.鼠标释放
### void MouseUp(char *button);  // 鼠标释放

## 5.鼠标滚轮移动
### void MouseRoll(int move);  // 鼠标滚轮,正数向上负数向下

## 6.键盘按下
### void KeyDown(char *key);  // 键盘按下

## 7.键盘释放
### void KeyUp(char *key);  // 键盘释放

## 8.键盘模拟按下
### void PressKey(char *key); // 按键

## 9.键盘模拟输入(目前仅支持英文)
### void WriteStr(const char str_print[], int str_size); // 输入字符窜函数但仅可用英文,参数为需要输出的字符窜, 字符窜数组大小

## 10. 复制字符窜:
### void CopyStr(const char *str);  // 复制字符窜到剪切板

## 11.从剪切板获取内容
### PasteStrStructs PasteStr();  // 存储返回的字符窜内容，使用方法:
#### 
	PasteStrStructs str = PasteStr();  // 获取字符窜存入结构体
    printf("%s", str.text);  // 输出字符窜
    FreePasteStr(&str);  // 释放内存

## 12. 添加快捷键:
### void AddHotKey(char *key1, char *key2, char *key3, char *key4, void (*target_void_func)());  // 添加快捷键的函数不输入的传NULL
#### 使用方法:
#####     AddHotKey("ctrl", "l", NULL, NULL, ClearHotKey);  // 注册快捷键，第五个参数为回调函数
    AddHotKey("esc", NULL, NULL, NULL, ClearHotKey);  // 可注册多个快捷键
    ListenHotKEy();  // 监听快捷键  ClearHotKey在程序结束时必须调用用它来注销快捷键注册，比如ClearHotKey()
	
## 13.获取电脑分辨率（参数输入布偶值或者1与0）
### ScreenSizeGet GetScreenSIze(bool out_put);  // 获取分辨率函数，布偶值选择是否输出坐标, 使用方法
#### 1.输出坐标:    
	GetScreenSIze(1);  // 输出坐标内容
#### 2.将坐标存放在结构体再输出:    
	ScreenSizeGet screen =  GetScreenSIze(0);  // 输出坐标内容
    printf("%d:x, %d:y", screen.x, screen.y);
	
## 14.获取鼠标当前坐标:
### MousePositionGet GetMousePosition(bool out_put);  // 获取光标目前所在的坐标，鼠标坐标，布偶值选择是否输出坐标, 使用方法:
#### 1.输出当前坐标GetMousePosition(true);  // 获取鼠标当前坐标并输出
#### 2.将坐标存放在结构体:
	MousePositionGet position =  GetMousePosition(false);  // 获取鼠标当前坐标并输出
    printf("%ld:x, %ld:y", position.x, position.y);
	
## 15. 检查程序结束释放忘记释放的内存与按键

### void ExitCheckWork();  // 突然结束检查，在main函数声明后直接调用即可，程序结束会自动进行检查清理工作，比如KeyDown("a)忘记调用KeyUp("a)时，程序结束后它将会自动调用释放函数

# 总结:
## 本库是一个简单的有关c语言Windows操作的一个键鼠库，目前作者也在努力找bug努力更新努力增加新的功能，具体可用查看更新时间，下发有所声明，由于作者误删把之前库的文件全部清理了倒置上传失败，已经在努力修复bug了哦

# 更新提示:
## 2024/10/4发布:本次修改了一些小bug，由于作者木实粒暂时找不出错误点了，关于cpp配置问题已经解决，作者已经附加了cpp的Cmake配置并且完成测试可用正常使用