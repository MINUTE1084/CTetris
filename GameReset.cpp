#include "stdafx.h"

void Tetris::resetGameboard() {
	for (int i = 0; i < FRAME_HEIGHT; i++) { // �������� 0���� �ʱ�ȭ  
		for (int j = 0; j < FRAME_WIDTH; j++) {
			Gameboard[0][i][j] = 0;
			Gameboard[1][i][j] = BLACK;
		}
	}
	for (int i = 1; i < FRAME_HEIGHT - 1; i++) { //�¿� ��  
		Gameboard[0][i][0] = WALL;
		Gameboard[0][i][FRAME_WIDTH - 1] = WALL;
		Gameboard[1][i][0] = WHITE;
		Gameboard[1][i][FRAME_WIDTH - 1] = WHITE;
	}
	for (int j = 0; j < FRAME_WIDTH; j++) { //�ٴ�
		Gameboard[0][FRAME_HEIGHT - 1][j] = WALL;
		Gameboard[1][FRAME_HEIGHT - 1][j] = WHITE;
	}
}

void Tetris::resetCopiedGameboard() {
	for (int i = 0; i < FRAME_HEIGHT; i++) {
		for (int j = 0; j < FRAME_WIDTH; j++) {
			copiedGameboard[0][i][j] = 500;
			copiedGameboard[1][i][j] = 500;
		}
	}
}


