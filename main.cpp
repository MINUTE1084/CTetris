#include "stdafx.h"

int main() {
	srand((unsigned)time(NULL));
	removeCursor();
	system("mode con cols=56 lines=30");
	Tetris *T = new Tetris();
	T->title();

	while (1) {
		for (int i = 0; i < 5; i++) { // Can get key inpur 5 times
			T->keyCheck();
			T->drawGameboard();
			Sleep(T->getSpeed());
			if (T->getEvent(0) && T->checkCollision(T->getPos(0), T->getPos(1), T->getRotation())) Sleep(100); // if block can't move down, Delay
		}
		T->dropBlock();
		T->checkLvUp();
		if (T->checkGameOver()) break; // if currently game over, break while (end game)
		if (T->getEvent(1)) T->generateNewBlock(); // if need new block, generate block
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