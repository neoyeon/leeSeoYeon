#include "main.h"
#include "game.h"

int main() {
	init();
	//시작화면. 헷갈려서 만들어둔거니 지우고 하시면 됩니당
	while (1)
	{
		titleDraw();
		loveGauge();
		int n = keyControl();
		if (n == SUBMIT) {
			return 0;
		}
	}
	return 0;


	
}