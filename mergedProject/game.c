#include "game.h"

//Ű ����
int keyControl() {
	char temp = getch();

	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') { //�����̽���(����)
		return SUBMIT;
	}
}

//����ȭ�� ����ϱ�
void titleDraw() {
	printf("����ȭ��");
}

//����������
void loveGauge() {

	//Ʋ
	int x = 10;
	int y = 37;
	gotoxy(x - 2, y - 1);
	printf("====================================================================================\n");
	gotoxy(x - 2, y);
	printf("||");
	gotoxy(x, y);
	//printf("################################################################################"); //80����
	printf("                                                                                "); //���۰�����. ����
	gotoxy(100 - x, y);
	printf("||");
	gotoxy(x - 2, y + 1);
	printf("====================================================================================\n");

	//������ ������
	int a = 1; // a �� �����̽��ٸ� ���� ������ �ٲ�� ��. �ٿ��� �ڵ� ¥���� �����ҰԿ�
	for (int i = 0; i <= 80 / 2; i++) {
		if (a == 1) { // 1 �� �� ������
			Sleep(1000);
			gotoxy(x, y);

			for (int love = 0; love < i; love++) {
				printf("##");
			}
		}
		else { // a �� 1�� �ƴ� �� ������
			gotoxy(x, y);

			for (int nlove = 0; nlove >= 0; nlove--) {
				printf("##");
			}
		}
	}
	gotoxy(30, 10);
	printf("���� ��������"); // ���� ���������� �Ѿ�� �� ª�� �ִϸ��̼� �־ ���� ��
}