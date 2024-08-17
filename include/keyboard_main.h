#ifndef KEYBOARD_MAIN_H
#define KEYBOARD_MAIN_H
#include <windows.h>
#include <stdbool.h>


/************* press up flag **************/

typedef struct PressUpFlag  // ���մ���û���ͷŵİ�ť,trueΪ�ͷ�
{
    bool key_up_3;  // ������ݼ�
    bool key_up_2;  // ������ݼ�
    bool key_up_1;  // һ����ݼ�
    bool mouse_up; // ���̧���־
    bool key_ctrl;   // �ж�ctrl
    bool key_shift;  // �ж�shift
    bool key_alt;  // �ж�alt
    bool key_win;       // win����
    int key_name;  // ��������������ƣ�����������
    char *mouse_name;  // ���������������
}Flags;

Flags flag_up = {true, true, true, true, true, true, true, true, 0, NULL};  // Ĭ��û̧��

/******************************************/

typedef struct ScreenSize  // �����ṹ���ȡ��Ļ��С
{
    int x;
    int y;
} ScreenSizeGet;  // �����ǩ

/************ ��갴�����ͷ� ************/
typedef struct
{
    char *button;
}MouseDownAndUp;  // ������갴�»����ͷŵĽṹ��


/********************************************************/
typedef struct MousePosition  // ��ȡ������ڵ�ǰλ��
{
    LONG x;
    LONG y;
}MousePositionGet;
/*********************** �� �����ַ��ܵĽṹ�� *******************/
typedef struct copy_str_structs  // �ַ��ܼ��еĽṹ��(��ֹ�����ظ�������ͬ�ַ���)
{
    const char* textToCopy;  // һ������ָ���ַ���
    void (*copy_str_in)(struct copy_str_structs);  // ���Ƶ����а�ĺ���������������CopyStr��
}copy_str_structs;

/***************** ע���ݼ� *********************/

// ����һ���ṹ�����洢��ݼ���Ϣ
typedef struct HotKey
{
    char *key1;          // ��һ������
    char *key2;          // �ڶ�������
    char *key3;          // ����������
    char *key4;          // ���ĸ�����
    void (*function)(void);  // �����õĺ���ָ��
} AddHotKeyInput;  // ���ܴ���Ĳ���(��ݼ�����)

// ʹ��һ���������洢�����ݼ�
typedef struct HotKeyList
{
    AddHotKeyInput data;  // ��ݼ�����, �洢һ�� AddHotKeyInput �ṹ��ʵ��������ݼ������ݡ�
    struct HotKeyList *next;  // ָ����һ����¼��ָ�룬ָ����һ�� HotKeyList �ṹ��ʵ����ָ�룬�������Ӷ���ڵ��γ�����
} HotKeyList;

/********* ��ȡ���а����� *********/
typedef struct {
    char* text; // ָ��������ı���ָ��
    size_t length; // �ı�����
}PasteStrStructs;



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);  // ��ݼ��ص�����

void freeHotKeys();  // �ͷŽṹ���ڴ溯��

void RegisterHotKeys();  // // ע��һ�����̵ͼ����ӣ�������ݼ�

/********************************************/

void copy_str_in(copy_str_structs self);  // ���Ƶ����а�ĺ���������������CopyStr������



/*********************************************************************************/
void MouseMoveTo(int x, int y);  // x,y����;

void MouseDown(char *button);  // ��갴�¼�λ

void MouseUp(char *button);  // ����ͷ�

void MouseClick(int x, int y, int clicks, char button[]);  // ���������

//void GetScreenSIze();  // ��ȡ�ֱ��ʺ���(����)

//void GetMousePosition();  // ��ȡ���Ŀǰ���ڵ�����(����)

void MouseRoll(int move);  // ������,�������ϸ�������

void KeyDown(char *key);  // ���̰���

void KeyUp(char *key);  // �����ͷ�

void PressHotKey(char *key1, char *key2, char *key3);  // ���¿�ݼ�

void PressKey(char *key); // ����

void WriteStr(const char str_print[], int str_size); // �����ַ��ܺ�����������Ӣ��

void CopyStr(const char *str);  // �����ַ��ܵ����а�

void FreePasteStr(PasteStrStructs * clipboardText); // ����������ʵ�����Ľṹ�壬�ͷŻ�ȡ����������ʱ������ڴ�(�ݴ�)

void AddHotKey(char *key1, char *key2, char *key3, char *key4, void (*target_void_func)());  // ��ӿ�ݼ��ĺ���������Ĵ�NULL

void ClearHotKey(); // ע����ݼ�(�Զ�ע����ݼ������ͷ��ڴ�ĺ���)

void ListenHotKEy();  // ������ݼ�


/************* ��ȡ����ĺ��� ***************/
ScreenSizeGet GetScreenSIze(bool out_put);  // ��ȡ�ֱ��ʺ�������żֵѡ���Ƿ��������

MousePositionGet GetMousePosition(bool out_put);  // ��ȡ���Ŀǰ���ڵ����꣬������꣬��żֵѡ���Ƿ��������

PasteStrStructs PasteStr();  // �洢���ص��ַ�������


/******************** β������ ******************/
void ReleaseKey(WORD vkCode, bool *keyUpFlag);  // ȷ�������汻����
void cleanup_check();  // ִ����������ĺ���
void handle_sigint(int sig);  // ����Ƿ񱻽��ܵ���ֹ�ź�
void exit_check_work();  // ͻȻ�������



#endif