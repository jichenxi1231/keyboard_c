#include <stdio.h>
#include "include/keyboard_main.h"
#include <stdbool.h>
#include <pthread.h>

int main()
{
    MousePositionGet position =  GetMousePosition(false);  // ��ȡ��굱ǰ���겢���
    printf("%ld:x, %ld:y", position.x, position.y);

//    ScreenSizeGet screen =  GetScreenSIze(0);  // �����������
//    printf("%d:x, %d:y", screen.x, screen.y);

//    AddHotKey("ctrl", "l", NULL, NULL, ClearHotKey);  // ע���ݼ������������Ϊ�ص�����
//    AddHotKey("esc", NULL, NULL, NULL, ClearHotKey);  // ��ע������ݼ�
//    ListenHotKEy();  // ������ݼ�  ClearHotKey�ڳ������ʱ�������������ע����ݼ�ע�ᣬ����ClearHotKey()

//    PasteStrStructs str = PasteStr();  // ��ȡ�ַ��ܴ���ṹ��
//    printf("%s", str.text);  // ����ַ���
//    FreePasteStr(&str);  // �ͷ��ڴ�
    return 0;
}