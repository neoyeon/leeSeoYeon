#include "util.h"

//�Լ� ����
void init() {
	system("mode con cols=100 lines=40 | title ������ �ٶ�"); //�̰ɷ� �ܼ� ũ�� ����

	//Ŀ�� �Ⱥ��̰� ����
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}


//Ŀ�� ��ġ �̵��Լ�
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);

}