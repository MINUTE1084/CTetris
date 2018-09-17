#pragma once
#define UP								72
#define DOWN						80
#define LEFT							75
#define RIGHT						77
#define SPACE						32

#define WIDTH						60
#define HEIGHT						80
#define FRAME_WIDTH		12
 #define FRAME_HEIGHT		22
#define BOARD_X					3
#define BOARD_Y					3

#define SHADOW_BLOCK		97
#define ACTIVE_BLOCK		98
#define CEILLING					99
#define EMPTY						100 
#define WALL						101
#define INACTIVE_BLOCK	102

#define YELLOW					0
#define CYAN							1
#define RED							2
#define GREEN						3
#define ORANGE					4
#define BLUE							5
#define PURPLE					6
#define BLACK						7
#define WHITE						8

void gotoxy(int x, int y);
void removeCursor();
