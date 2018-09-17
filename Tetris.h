#pragma once
class Tetris
{
private:
	int blocks[7][4][4][4] = {
		{ // O
			{
				0,0,0,0,
				0,1,1,0,
				0,1,1,0,
				0,0,0,0
			},

		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0
		},

		{
			0,0,0,0
			,0,1,1,0,
		0,1,1,0,
		0,0,0,0
		},

		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0
		}
		},

	{ // I
		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			0,0,0,0
		},

		{
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
			0,1,0,0
		},

		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,1,
			0,0,0,0
		},

		{
			0,1,0,0,
			0,1,0,0,
			0,1,0,0,
			0,1,0,0
		}
	},

	{ // Turn - N
		{
			0,0,0,0,
			1,1,0,0,
			0,1,1,0,
			0,0,0,0
		},

		{
			0,0,0,0,
			0,0,1,0,
			0,1,1,0,
			0,1,0,0
		},

		{
			0,0,0,0,
			1,1,0,0,
			0,1,1,0,
			0,0,0,0
		},

		{
			0,0,0,0,
			0,0,1,0,
			0,1,1,0,
			0,1,0,0
		}
	},

	{ // N
		{
			0,0,0,0,
			0,1,1,0,
			1,1,0,0,
			0,0,0,0
		},

		{
			0,0,0,0,
			1,0,0,0,
			1,1,0,0,
			0,1,0,0
		},

		{
			0,0,0,0,
			0,1,1,0,
			1,1,0,0,
			0,0,0,0
		},

		{
			0,0,0,0,
			1,0,0,0,
			1,1,0,0,
			0,1,0,0
		}
	},

	{ // L
		{
			0,0,0,0,
			0,0,1,0,
			1,1,1,0,
			0,0,0,0
		},

		{
			0,0,0,0,
			1,1,0,0,
			0,1,0,0,
			0,1,0,0
		},

		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,0,
			1,0,0,0
		},

		{
			0,0,0,0,
			0,1,0,0,
			0,1,0,0,
			0,1,1,0
		}
	},

	{ // Turn-L
		{
			0,0,0,0,
			1,0,0,0,
			1,1,1,0,
			0,0,0,0
		},

		{
			0,0,0,0,
			0,1,0,0,
			0,1,0,0,
			1,1,0,0
		},

		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,0,
			0,0,1,0
		},

		{
			0,0,0,0,
			0,1,1,0,
			0,1,0,0,
			0,1,0,0
		}
	},

	{ // T
		{
			0,0,0,0,
			0,1,0,0,
			1,1,1,0,
			0,0,0,0
		},

		{
			0,0,0,0,
			0,1,0,0,
			0,1,1,0,
			0,1,0,0
		},

		{
			0,0,0,0,
			0,0,0,0,
			1,1,1,0,
			0,1,0,0
		},

		{
			0,0,0,0,
			0,1,0,0,
			1,1,0,0,
			0,1,0,0
		}
	}
	}; // block[block_type][block_rotation][y][x]

	int Gameboard[2][FRAME_HEIGHT][FRAME_WIDTH];
	int copiedGameboard[2][FRAME_HEIGHT][FRAME_WIDTH];

	int speed; 
	int level;
	int cnt; // remaining line
	int score;
	int block;
	int nextBlock;
	int holdBlock;
	int rotation;

	bool isOnBlock;
	bool isNeedNewBlock;
	bool isHoldUsed;
	bool isGMmode;

	COORD pos, shadowPos;
public:
	Tetris();
	void title();
	void LevelChoose();
	void setLevel(int selLevel);

	int getSpeed() { return speed; }
	int getRotation() { return rotation; }
	int getEvent(int type); // 0 = isOnBlock, 1 = isNeedNewBlock
	int getPos(int type); // 0 : x, 1 : y

	void resetGameboard(); // Reset Gameboard[0]
	void resetCopiedGameboard(); // Reset CopiedGameboard[0]

	void shadowRemove();
	void shadowDraw(int dirX = 0, int dirY = 0);

	void generateNewBlock(); // New block generate
	void dropBlock(); // Drop a block one line
	void holdingBlock(); // Holding Block
	void moveBlock(int dir); // Moving block using key input
	int checkCollision(int x, int y, int r); // Checking collision

	void drawInfo(); // Drawing information
	void drawGameboard(); // Drawing Gameboard[0]
	void colorSetting(int data); // Setting Color

	void keyCheck(); // Checking key
	void checkLine(); // Checking line is full
	void checkLvUp(); // Checking remaining line is 0
	bool checkGameOver(); // Checking Gameboard[0] is full
};

