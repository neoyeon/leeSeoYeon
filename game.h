#include "main.h"

#ifndef KEY_CODE
#define KEY_CODE

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 //����(�����̽���)

#endif

//�Լ�����
void init();
int keyControl();
void mainDraw();
void loveGauge();

void titleDraw();
int menuDraw();
void infoDraw();
void girlfriend_back(); // �Ⱥ��� ��
void girlfriend_see();  //  ���� ��
void girlFriendTime(); // ����ģ���� ���ƺ��� �ִ� �ð�.
void random();
void badEnd();

//���� ����
void start();
void mainScreen();

