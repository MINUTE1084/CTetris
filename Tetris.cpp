#include "stdafx.h"
#include "Tetris.h"

Tetris::Tetris()
{
	speed = 100;
	level = 1;
	cnt = 0;
	score = 0;
	isHoldUsed = 0;
	isGMmode = 0;
}

void Tetris::title()
{
	colorSetting(WHITE);
	while (1) {
		int y = 10; // 3
		gotoxy(7, y++); colorSetting(y - 11); printf("□□□□□□□□□□□□□");
		gotoxy(7, y++); colorSetting(y - 11);  printf("□                      □");
		gotoxy(7, y++); colorSetting(y - 11); printf("□   T  E  T  R  I  S   □");
		gotoxy(7, y++); colorSetting(y - 11); printf("□    G  R  A  N  D     □");
		gotoxy(7, y++); colorSetting(y - 11); printf("□   M  A  S  T  E  R   □");
		gotoxy(7, y++); colorSetting(y - 11); printf("□                      □");
		gotoxy(7, y++); colorSetting(y - 11); printf("□□□□□□□□□□□□□");
		gotoxy(7, y++);	colorSetting(y - 10); printf(" Press Enter Key to Start");

		if (_kbhit()) {
			int key = _getch();
			if (key == 13) break;
		}
	}

	LevelChoose();
}

void Tetris::LevelChoose() {
	bool isExit = true;
	int selLevel = 1;
	while (isExit) {
		int y = 10; // 3
		gotoxy(7, y++); colorSetting(y - 11);	 printf("□□□□□□□□□□□□□");
		gotoxy(7, y++); colorSetting(y - 11);	 printf("□                      □");
		gotoxy(7, y++); colorSetting(y - 11);	 printf("□   S  E  L  E  C  T   □");
		gotoxy(7, y++); colorSetting(y - 11);	 printf("□    L  E  V  E  L     □");
		gotoxy(7, y++); colorSetting(y - 11);	 if (selLevel == 10)	printf("□      >  G  M  <      □"); else	 printf("□      >  0  %d  <      □", selLevel);
		gotoxy(7, y++); colorSetting(y - 11);	 printf("□                      □");
		gotoxy(7, y++); colorSetting(y - 11);	 printf("□□□□□□□□□□□□□");
		gotoxy(5, y++);	colorSetting(y - 10); printf(" Press ←/→ Keys to Select Level");
		gotoxy(7, y++);	colorSetting(y - 10); printf(" Press Enter Key to Start");

		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case LEFT:
				if (selLevel > 1) selLevel--;
				break;

			case RIGHT:
				if (selLevel < 10) selLevel++;
				break;

			case 13:
				isExit = false;
				break;
			}
		}
	}
	system("cls");
	resetGameboard();
	drawInfo();
	drawGameboard();

	setLevel(selLevel);
	nextBlock = rand() % 7;
	holdBlock = -1;
	generateNewBlock();
}

void Tetris::setLevel(int selLevel) {
	level = selLevel;
	for (int i = 0; i < selLevel - 1; i++) speed -= 10;
	if (level < 10) drawInfo();
	else checkLvUp();
}

void Tetris::dropBlock()
{
	if (isOnBlock && checkCollision(pos.X, pos.Y + 1, rotation)) isOnBlock = 0;
	if (isOnBlock && !checkCollision(pos.X, pos.Y + 1, rotation)) {
		for (int i = 0; i < FRAME_HEIGHT; i++) { 
			for (int j = 0; j < FRAME_WIDTH; j++) {
				if (Gameboard[0][i][j] == ACTIVE_BLOCK) {
					Gameboard[0][i][j] = INACTIVE_BLOCK;
					Gameboard[1][i][j] = block;
				}
			}
		}
		isOnBlock = 0; 
		isHoldUsed = 0;
		isNeedNewBlock = 1;
		checkLine();
		return; 
	}
	if (checkCollision(pos.X, pos.Y + 1, rotation)) moveBlock(DOWN);
	else isOnBlock++; 
}

void Tetris::holdingBlock()
{
	if (!isHoldUsed) {
		isHoldUsed = 1;
		shadowRemove();
		for (int i = 0; i < 4; i++) { //게임판 pos.X, pos.Y위치에 블럭생성  
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j] = EMPTY;
					Gameboard[1][pos.Y + i][pos.X + j] = BLACK;
				}
			}
		}
		if (holdBlock == -1) {
			holdBlock = block;
			generateNewBlock();
		}
		else {
			int Temp = block;
			block = holdBlock;
			holdBlock = Temp;
			pos.X = (FRAME_WIDTH / 2) - 1;
			pos.Y = 0;
			rotation = 0;
			shadowRemove();
			shadowDraw();
		}
		colorSetting(holdBlock);
		for (int i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 
			for (int j = 0; j < 4; j++) {
				if (blocks[holdBlock][0][i][j] == 1) {
					gotoxy(FRAME_WIDTH + BOARD_X + 2 + j, i + 12);
					printf("■");
				}
				else {
					gotoxy(FRAME_WIDTH + BOARD_X + 2 + j, i + 12);
					printf("  ");
				}
			}
		}
	}
}


void Tetris::generateNewBlock()
{
	isNeedNewBlock = 0;
	pos.X = (FRAME_WIDTH / 2) - 1; //블록 생성 위치x좌표(게임판의 가운데) 
	pos.Y = 0;  //블록 생성위치 y좌표(제일 위) 
	block = nextBlock; //다음블럭값을 가져옴 
	nextBlock = rand() % 7; //다음 블럭을 만듦 
	rotation = 0;  //회전은 0번으로 가져옴 

	for (int i = 0; i < 4; i++) { //게임판 pos.X, pos.Y위치에 블럭생성  
		for (int j = 0; j < 4; j++) {
			if (blocks[block][rotation][i][j] == 1) {
				Gameboard[0][pos.Y + i][pos.X + j] = ACTIVE_BLOCK;
				Gameboard[1][pos.Y + i][pos.X + j] = block;
			}
		}
	}
	colorSetting(nextBlock);
	for (int i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 
		for (int j = 0; j < 4; j++) {
			if (blocks[nextBlock][0][i][j] == 1) {
				gotoxy(FRAME_WIDTH + BOARD_X + 2 + j, i + 6);
				printf("■");
			}
			else {
				gotoxy(FRAME_WIDTH + BOARD_X + 2 + j, i + 6);
				printf("  ");
			}
		}
	}
	shadowDraw(0,0);
}

int Tetris::checkCollision(int x, int y, int r)
{
 	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) { //지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 false를 리턴 
			if (blocks[block][r][i][j] == 1 && Gameboard[0][y + i][x + j] > 100) return false;
		}
	}
	return true; //하나도 안겹치면 true리턴 
}


void Tetris::moveBlock(int dir)
{
	
	switch (dir) {
	case LEFT:
		shadowRemove();
		for (int i = 0; i < 4; i++) { 
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j] = EMPTY;
					Gameboard[1][pos.Y + i][pos.X + j] = BLACK;
				}
			}
		}
		shadowDraw(-1);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j - 1] = ACTIVE_BLOCK;
					Gameboard[1][pos.Y + i][pos.X + j - 1] = block;
				}
			}
		}
		pos.X--;
		break;

	case RIGHT: 
		shadowRemove();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j] = EMPTY;
					Gameboard[1][pos.Y + i][pos.X + j] = BLACK;
				}
			}
		}
		shadowDraw(1);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j + 1] = ACTIVE_BLOCK;
					Gameboard[1][pos.Y + i][pos.X + j + 1] = block;
				}
			}
		}
		pos.X++;
		break;

	case DOWN:
		shadowRemove();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j] = EMPTY;
					Gameboard[1][pos.Y + i][pos.X + j] = BLACK;
				}
			}
		}
		shadowDraw();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i + 1][pos.X + j] = ACTIVE_BLOCK;
					Gameboard[1][pos.Y + i + 1][pos.X + j] = block;
				}
			}
		}
		pos.Y++;
		break;

	case UP:
		shadowRemove();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j] = EMPTY;
					Gameboard[1][pos.Y + i][pos.X + j] = BLACK;
				}
			}
		}
		rotation = (rotation + 1) % 4;
		shadowDraw();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j] = ACTIVE_BLOCK;
					Gameboard[1][pos.Y + i][pos.X + j] = block;
				}
			}
		}
		break;

	case 100:
		shadowRemove();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i][pos.X + j] = EMPTY;
					Gameboard[1][pos.Y + i][pos.X + j] = BLACK;
				}
			}
		}
		rotation = (rotation + 1) % 4;
		shadowDraw(0,-1);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (blocks[block][rotation][i][j] == 1) {
					Gameboard[0][pos.Y + i - 1][pos.X + j] = ACTIVE_BLOCK;
					Gameboard[1][pos.Y + i - 1][pos.X + j] = block;
				}
			}
		}
		pos.Y--;
		break;
	}
}

void Tetris::keyCheck()
{
	int key = 0; 

	if (_kbhit()) {  
		key = _getch();
		if (key == 224) { 
			do { key = _getch(); } while (key == 224);
			switch (key) {
			case LEFT:
				if (checkCollision(pos.X - 1, pos.Y, rotation)) moveBlock(LEFT);
				break;
			case RIGHT: 
				if (checkCollision(pos.X + 1, pos.Y, rotation)) moveBlock(RIGHT);
				break;
			case DOWN: 
				if (checkCollision(pos.X, pos.Y + 1, rotation)) moveBlock(DOWN);
				break;
			case UP:
				if (checkCollision(pos.X, pos.Y, (rotation + 1) % 4)) moveBlock(UP);
				else if (isOnBlock == 1 && checkCollision(pos.X, pos.Y, (rotation + 1) % 4)) moveBlock(100);
				break;
			} 
		}
		else {  
			switch (key) {
			case SPACE:
				while (isOnBlock == 0) {
					dropBlock();
					score++; // hard drop 보너스
					colorSetting(WHITE);
					gotoxy(FRAME_WIDTH + BOARD_X, 5); printf(" Score : %5d", score);
				}
				break;
			case 'H':
			case 'h':
				holdingBlock();
				break;
			}
		}
	}
	while (_kbhit()) _getch();
}

