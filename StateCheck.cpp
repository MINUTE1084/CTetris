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
		if (block_amount == FRAME_WIDTH - 2) { //����� ���� �� ��� 

			if (!isGMmode) score += 100 * level; //�����߰� 
			else score += 200 * level; //�����߰� 
			cnt++; //���� �� ���� ī��Ʈ ���� 
			combo++; //�޺��� ����  
	
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
		level++; //������ 1 �ø� 
		if (cnt == 10) cnt = 0; //���� �ټ� �ʱ�ȭ   
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
				case EMPTY: //��ĭ��� 
					printf("  ");
					break;
				case WALL: //����� 
					printf("��");
					break;
				case INACTIVE_BLOCK: //���� �� ���  
					printf("��");
					break;
				case ACTIVE_BLOCK: //�����̰��ִ� �� ���  
					printf("��");
					break;
				case SHADOW_BLOCK: //�׸��� �� ���  
					printf("��");
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
					case EMPTY: //��ĭ��� 
						printf("  ");
						break;
					case WALL: //����� 
						printf("��");
						break;
					case INACTIVE_BLOCK: //���� �� ���  
						printf("��");
						break;
					case ACTIVE_BLOCK: //�����̰��ִ� �� ���  
						printf("��");
						break;
					case SHADOW_BLOCK: //�׸��� �� ���  
						printf("��");
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
