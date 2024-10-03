#ifndef KEYBOARD_MAIN_H
#define KEYBOARD_MAIN_H
#include <windows.h>
#include <stdbool.h>
#define True 1
#define False 0

/************* press up flag **************/

typedef struct
{
    bool mouse_up;
    const char *mouse_name;
}MouseUps;
MouseUps flag_up = {true, ""};

typedef struct PressHotKeyNameUp
{
    int key_num;  // ���µ�����
    int key_code[108];
}PressHotKeyNameUp;  // �ͷŰ��µİ���
PressHotKeyNameUp free_keys = {0, 0}; // �ͷŰ���

/******************************************/

typedef struct ScreenSize  // �����ṹ���ȡ��Ļ��С
{
    int x;
    int y;
} ScreenSizeGet;  // �����ǩ

/************ ��갴�����ͷ� ************/
typedef struct
{
    const char *button;
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
    const char *key1;          // ��һ������
    const char *key2;          // �ڶ�������
    const char *key3;          // ����������
    const char *key4;          // ���ĸ�����
//    void (*function)(void);  // �����õĺ���ָ��
} AddHotKeyInput;  // ���ܴ���Ĳ���(��ݼ�����)

// ʹ��һ���������洢�����ݼ�
typedef struct HotKeyList
{
    AddHotKeyInput data;  // ��ݼ�����, �洢һ�� AddHotKeyInput �ṹ��ʵ��������ݼ������ݡ�
    struct HotKeyList *next;  // ָ����һ����¼��ָ�룬ָ����һ�� HotKeyList �ṹ��ʵ����ָ�룬�������Ӷ���ڵ��γ�����
} HotKeyList;

// ����һ������ָ������
typedef void (*FunctionPtr)();

// ����һ����������ṹ��
typedef struct
{
    /********** �ĸ���ݼ������С *********/
    int size_four_key_ctrl_alt_shift;
    int size_four_key_ctrl_shift_alt;
    int size_four_key_alt_ctrl_shift;
    int size_four_key_alt_shift_ctrl;
    int size_four_key_shift_ctrl_alt;
    int size_four_key_shift_alt_ctrl;
////////////////////////////////////////////
    int size_three_ctrl_alt;  // ������ݼ�
    int size_three_ctrl_shift;
    int size_three_alt_ctrl;
    int size_three_alt_shift;
    int size_three_shift_ctrl;
    int size_three_shift_alt;
///////////////////////////////////////////////
    int size_two_ctrl;  // ˫��ݼ�
    int size_two_alt;
    int size_two_shift;

    int size_one;

    /**** �ĸ���ݼ����� ****/
    const char*four_key_name_ctrl_alt_shift[53];
    const char*four_key_name_ctrl_shift_alt[53];
    const char*four_key_name_alt_ctrl_shift[53];
    const char*four_key_name_alt_shift_ctrl[53];
    const char*four_key_name_shift_ctrl_alt[53];
    const char*four_key_name_shift_alt_ctrl[53];


///////////////////////////////////////////////////////
    const char*three_key_name_ctrl_alt[53];  // ����ݼ�
    const char*three_key_name_ctrl_shift[53];
    const char*three_key_name_alt_ctrl[53];
    const char*three_key_name_alt_shift[53];
    const char*three_key_name_shift_ctrl[53];
    const char*three_key_name_shift_alt[53];

    const char*tow_key_name_ctrl[53];  // ˫��ݼ�
    const char*tow_key_name_alt[53];
    const char*tow_key_name_shift[53];

    const char*one_key_name[53];

    FunctionPtr *funcArray_four_key_ctrl_alt_shift;
    FunctionPtr *funcArray_four_key_ctrl_shift_alt;
    FunctionPtr *funcArray_four_key_alt_ctrl_shift;
    FunctionPtr *funcArray_four_key_alt_shift_ctrl;
    FunctionPtr *funcArray_four_key_shift_ctrl_alt;
    FunctionPtr *funcArray_four_key_shift_alt_ctrl;

    // ������ݼ�
    FunctionPtr *funcArray_three_key_ctrl_alt;
    FunctionPtr *funcArray_three_key_ctrl_shift;
    FunctionPtr *funcArray_three_key_alt_ctrl;
    FunctionPtr *funcArray_three_key_alt_shift;
    FunctionPtr *funcArray_three_key_shift_ctrl;
    FunctionPtr *funcArray_three_key_shift_alt;

    FunctionPtr *funcArray_two_key_ctrl;  // ˫��ݼ�
    FunctionPtr *funcArray_two_key_alt;
    FunctionPtr *funcArray_two_key_shift;

    FunctionPtr *funcArray_one_key;

}Func_List;  // ��Ͽ�ݼ�ע�����ж�


/********* ��ȡ���а����� *********/
typedef struct {
    char* text; // ָ��������ı���ָ��
    size_t length; // �ı�����
}PasteStrStructs;



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);  // ��ݼ��ص�����

void freeHotKeys();  // �ͷŽṹ���ڴ溯��


/********************************************/

void copy_str_in(copy_str_structs self);  // ���Ƶ����а�ĺ���������������CopyStr������



/***************************** �������� **************************************************/
void MouseMoveTo(int x, int y);  // x,y����;

void MouseDown(const char *button);  // ��갴�¼�λ

void MouseUp(const char *button);  // ����ͷ�

void MouseClick(int x, int y, int clicks, char button[]);  // ���������

//void GetScreenSIze();  // ��ȡ�ֱ��ʺ���(����)

//void GetMousePosition();  // ��ȡ���Ŀǰ���ڵ�����(����)

void MouseRoll(int move);  // ������,�������ϸ�������

void KeyDown(const char *key);  // ���̰���

void KeyUp(const char *key);  // �����ͷ�

void PressHotKey(const char *key1, const char *key2, const char *key3);  // ���¿�ݼ�

void PressKey(const char *key); // ����

void WriteStr(const char str_print[], int str_size); // �����ַ��ܺ�����������Ӣ��

void CopyStr(const char *str);  // �����ַ��ܵ����а�

void FreePasteStr(PasteStrStructs * clipboardText); // ����������ʵ�����Ľṹ�壬�ͷŻ�ȡ����������ʱ������ڴ�(�ݴ�)

void AddHotKey(const char *key1, const char *key2, const char *key3, const char *key4, void (*target_void_func)());  // ��ӿ�ݼ��ĺ���������Ĵ�NULL

void ClearHotKey(); // ע����ݼ�(�Զ�ע����ݼ������ͷ��ڴ�ĺ���)

void ListenHotKEy();  // ������ݼ�

void ExitCheckWork();  // ͻȻ�������


/************* ��ȡ����ĺ��� ***************/
ScreenSizeGet GetScreenSIze(bool out_put);  // ��ȡ�ֱ��ʺ�������żֵѡ���Ƿ��������

MousePositionGet GetMousePosition(bool out_put);  // ��ȡ���Ŀǰ���ڵ����꣬������꣬��żֵѡ���Ƿ��������

PasteStrStructs PasteStr();  // �洢���ص��ַ�������


/*************** �������������жϺ��� (�ʺ���Ϸ) ****************/
bool KeyUpListen( const char *key);  // ��������̧��
bool KeyDownListen(const char *key); // �������̰���


/******************** β������ ******************/
void cleanup_check();  // ִ����������ĺ���
void handle_sigint(int sig);  // ����Ƿ񱻽��ܵ���ֹ�ź�
void free_funcs();  // �ͷź����ڴ�



#endif