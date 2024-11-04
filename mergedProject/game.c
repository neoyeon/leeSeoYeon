#include "game.h"

//키 조종
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
	else if (temp == ' ') { //스페이스바(공백)
		return SUBMIT;
	}
}

//메인화면 출력하기
void titleDraw() {
	printf("시작화면");
}

//게이지구현
void loveGauge() {

	//틀
	int x = 10;
	int y = 37;
	gotoxy(x - 2, y - 1);
	printf("====================================================================================\n");
	gotoxy(x - 2, y);
	printf("||");
	gotoxy(x, y);
	//printf("################################################################################"); //80글자
	printf("                                                                                "); //시작게이지. 공백
	gotoxy(100 - x, y);
	printf("||");
	gotoxy(x - 2, y + 1);
	printf("====================================================================================\n");

	//게이지 차오름
	int a = 1; // a 는 스페이스바를 누를 때마다 바뀌는 값. 다예가 코딩 짜오면 수정할게용
	for (int i = 0; i <= 80 / 2; i++) {
		if (a == 1) { // 1 일 때 차오름
			Sleep(1000);
			gotoxy(x, y);

			for (int love = 0; love < i; love++) {
				printf("##");
			}
		}
		else { // a 가 1이 아닐 때 내려감
			gotoxy(x, y);

			for (int nlove = 0; nlove >= 0; nlove--) {
				printf("##");
			}
		}
	}
	gotoxy(30, 10);
	printf("다음 스테이지"); // 다음 스테이지로 넘어가기 전 짧은 애니메이션 있어도 좋을 듯
}