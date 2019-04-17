#include "stdafx.h"

int main() {
	srand((unsigned)time(NULL));
	removeCursor();
	system("mode con cols=56 lines=30");
	Tetris *T = new Tetris();
	T->title();

	while (1) {
		for (int i = 0; i < 5; i++) { // 최대 5회의 키 입력
			T->keyCheck();
			T->drawGameboard();
			Sleep(T->getSpeed());
			if (T->getEvent(0) && T->checkCollision(T->getPos(0), T->getPos(1), T->getRotation())) Sleep(100); // 블럭 이동이 불가능 하다면 잠시 멈춤
		}
		T->dropBlock(); 
		T->checkLvUp();
		if (T->checkGameOver()) break; // 게임 오버 상태일 경우 게임을 진행하지 않음
		if (T->getEvent(1)) T->generateNewBlock(); // 블럭이 놓여진 상태일 때, 새 블럭 생성
	}
	delete T;
	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 13) break;
		}
	}
	return 0;
}