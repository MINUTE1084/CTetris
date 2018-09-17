#include "stdafx.h"

void Tetris::shadowRemove()
{
	shadowPos = pos;
	while (checkCollision(shadowPos.X, shadowPos.Y + 1, rotation)) shadowPos.Y++;
	for (int i = 0; i < 4; i++) { //현재좌표의 블럭을 지움 
		for (int j = 0; j < 4; j++) {
			if (blocks[block][rotation][i][j] == 1) {
				Gameboard[0][shadowPos.Y + i][shadowPos.X + j] = EMPTY;
				Gameboard[1][shadowPos.Y + i][shadowPos.X + j] = BLACK;
			}
		}
	}
}

void Tetris::shadowDraw(int dirX, int dirY)
{
	shadowPos = pos;
	while (checkCollision(shadowPos.X + dirX, shadowPos.Y + 1, rotation)) shadowPos.Y++;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[block][rotation][i][j] == 1) {
				Gameboard[0][shadowPos.Y + i + dirY][shadowPos.X + j + dirX] = SHADOW_BLOCK;
				Gameboard[1][shadowPos.Y + i + dirY][shadowPos.X + j + dirX] = block;
			}
		}
	}
}