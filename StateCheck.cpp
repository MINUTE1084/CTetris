#include "stdafx.h"

void Tetris::checkLine()
{
	int block_amount;
	int combo = 0;

	for (int i = FRAME_HEIGHT - 2; i > 3;) {
		block_amount = 0;
		for (int j = 1; j < FRAME_WIDTH - 1; j++) {
			if (Gameboard[0][i][j] > 100) block_amount++;
		}
		if (block_amount == FRAME_WIDTH - 2) { //블록이 가득 찬 경우 

			if (!isGMmode) score += 100 * level; //점수추가 
			else score += 200 * level; //점수추가 
			cnt++; //지운 줄 갯수 카운트 증가 
			combo++; //콤보수 증가  
	
			for (int k = i; k > 1; k--) {
				for (int l = 1; l < FRAME_WIDTH - 1; l++) {
					Gameboard[0][k][l] = Gameboard[0][k - 1][l];
					Gameboard[1][k][l] = Gameboard[1][k - 1][l];
				}
			}
		}
		else i--;
	}
	if (combo) {
		colorSetting(WHITE);
		gotoxy(FRAME_WIDTH + BOARD_X, 18); printf(" --%d LINE--", combo);
		if (combo > 1) {
			score += (combo*level * 10);
			Sleep(1000);
		}
		gotoxy(FRAME_WIDTH + BOARD_X, 18); printf("                           ", combo);
		if (isGMmode) { gotoxy(FRAME_WIDTH + BOARD_X, 4); printf(" Remain line : %5d", 20 - cnt); }
		else { gotoxy(FRAME_WIDTH + BOARD_X, 4); printf(" Remain line : %5d", 10 - cnt); }
		gotoxy(FRAME_WIDTH + BOARD_X, 5); printf(" Score : %5d", score);
	}
	resetCopiedGameboard();
	drawGameboard();
}

void Tetris::checkLvUp()
{
	if (!isGMmode && cnt >= 10) {
		drawGameboard();
		level++; //레벨을 1 올림 
		if (cnt == 10) cnt = 0; //지운 줄수 초기화   
		else cnt = cnt - 10;

		colorSetting(WHITE);
		gotoxy(FRAME_WIDTH + BOARD_X, 18);
		printf(" --LEVEL UP--");
		gotoxy(FRAME_WIDTH + BOARD_X, 19);
		printf(" --SPEED UP--");
		Sleep(1000);

		gotoxy(FRAME_WIDTH + BOARD_X, 18);
		printf("                              ");
		gotoxy(FRAME_WIDTH + BOARD_X, 19);
		printf("                              ");

		resetCopiedGameboard();

		Sleep(100);
		checkLine();
		speed -= 10;
		gotoxy(FRAME_WIDTH + BOARD_X, 3); printf(" Lv.%5d", level);
		gotoxy(FRAME_WIDTH + BOARD_X, 4); printf(" Remain line : %5d", 10 - cnt);
		gotoxy(FRAME_WIDTH + BOARD_X, 5); printf(" Score : %5d", score);

	}

	if (level >= 10 && !isGMmode) {
		isGMmode = 1;

		gotoxy(FRAME_WIDTH + BOARD_X, 18);
		printf(" --MASTER MODE--");
		gotoxy(FRAME_WIDTH + BOARD_X, 19);
		printf(" --INVISIBLE BLOCK--");
		Sleep(1000);

		gotoxy(FRAME_WIDTH + BOARD_X, 18);
		printf("                                              ");
		gotoxy(FRAME_WIDTH + BOARD_X, 19);
		printf("                                              ");
		resetGameboard();
		resetCopiedGameboard();
		drawGameboard();

		gotoxy(FRAME_WIDTH + BOARD_X, 3); printf(" Lv. MASTER", level);
		gotoxy(FRAME_WIDTH + BOARD_X, 4); printf(" Remain line : %5d", 20);
		gotoxy(FRAME_WIDTH + BOARD_X, 5); printf(" Score : %5d", score);
	}

	if (cnt >= 20 && isGMmode) {
		for (int i = 0; i < FRAME_HEIGHT; i++) {
			for (int j = 0; j < FRAME_WIDTH; j++) {
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
					printf("▣");
					break;
				case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
					printf("■");
					break;
				case SHADOW_BLOCK: //그림자 블럭 모양  
					printf("□");
					break;
				}
			}
		}
		gotoxy(FRAME_WIDTH + BOARD_X, 3); printf(" Lv. GRAND MASTER", level);
		gotoxy(FRAME_WIDTH + BOARD_X, 4); printf(" Remain line : %5d", 0);
		gotoxy(FRAME_WIDTH + BOARD_X, 5); printf(" Score : %5d", score);
		gotoxy(FRAME_WIDTH + BOARD_X, 18); printf(" --GAME CLEAR--");
		gotoxy(BOARD_X, BOARD_Y + FRAME_HEIGHT + 1); printf(" Press Enter Key to Exit Tetris");
		gotoxy(FRAME_WIDTH + BOARD_X + 1, 20);

		while (1) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 13) exit(0);
			}
		}
	}
}

bool Tetris::checkGameOver()
{
	for (int i = 1; i < FRAME_WIDTH - 2; i++) {
		if (Gameboard[0][3][i] > 100) {
			colorSetting(WHITE);
			gotoxy(FRAME_WIDTH + BOARD_X, 18); printf(" --GAME OVER--");
			for (int i = 0; i < FRAME_HEIGHT; i++) {
				for (int j = 0; j < FRAME_WIDTH; j++) {
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
						printf("▣");
						break;
					case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
						printf("■");
						break;
					case SHADOW_BLOCK: //그림자 블럭 모양  
						printf("□");
						break;
					}
				}
			}
			gotoxy(BOARD_X, BOARD_Y + FRAME_HEIGHT + 1); printf(" Press Enter Key to Exit Tetris");
			gotoxy(FRAME_WIDTH + BOARD_X + 1, 20);
			return true;
		}
	}
	return false;
}
