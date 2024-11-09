#include "main.h"

#ifndef KEY_CODE
#define KEY_CODE

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 //선택(스페이스바)

#endif

//함수선언
void init();
int keyControl();
void mainDraw();
void loveGauge();

void titleDraw();
int menuDraw();
void infoDraw();
void girlfriend_back();
void girlfriend_see();
void random();
void randomtime();

//게임 실행
void start();
void mainScreen();

