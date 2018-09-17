#include "stdafx.h"
void Tetris::drawInfo()
{
	int y = 3;
	colorSetting(WHITE);
	gotoxy(FRAME_WIDTH + BOARD_X, y++); printf(" Lv.%5d", level);
	gotoxy(FRAME_WIDTH + BOARD_X, y++); printf(" Remain line : %5d", 10 - cnt);
	gotoxy(FRAME_WIDTH + BOARD_X, y++); printf(" Score : %5d", score);
	gotoxy(FRAME_WIDTH + BOARD_X, y++); printf(" ----N E X T----");
	y += 4;
	gotoxy(FRAME_WIDTH + BOARD_X, y++); printf(" ---------------");
	gotoxy(FRAME_WIDTH + BOARD_X, y++); printf(" ----H O L D----");
	y += 4;
	gotoxy(FRAME_WIDTH + BOARD_X, y++); printf(" ---------------");
}


void Tetris::drawGameboard()
{
	for (int i = 0; i < FRAME_HEIGHT; i++) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int j = 0; j < FRAME_WIDTH; j++) {
			if (copiedGameboard[0][i][j] != Gameboard[0][i][j] || copiedGameboard[1][i][j] != Gameboard[1][i][j]) {
				gotoxy(BOARD_X + j, BOARD_Y + i);
				colorSetting(Gameboard[1][i][j]);
				switch (Gameboard[0][i][j]) {
				case EMPTY: //빈칸모양 
					printf("  ");
					break;
				case WALL: //벽모양 
					printf("▩");
					break;
				case INACTIVE_BLOCK: //굳은 블럭 모양  
					if (level >= 10) printf("  ");
					else printf("▣");
					break;
				case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
					printf("■");
					break;
				case SHADOW_BLOCK: //그림자 블럭 모양  
					if (level >= 10) printf("  ");
					else printf("□");
					break;
				}
			}
		}
	}
	for (int i = 0; i < FRAME_HEIGHT; i++) {
		for (int j = 0; j < FRAME_WIDTH; j++) {
			copiedGameboard[0][i][j] = Gameboard[0][i][j];
			copiedGameboard[1][i][j] = Gameboard[1][i][j];
		}
	}
}

void Tetris::colorSetting(int data)
{
	switch (data) {
	case YELLOW:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		break;
	case CYAN:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		break;
	case RED:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		break;
	case GREEN:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		break;
	case ORANGE:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		break;
	case BLUE:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		break;
	case PURPLE:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		break;
	case BLACK:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		break;
	case WHITE:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		break;
	}
}
