#include "stdafx.h"

int Tetris::getEvent(int type)
{
	switch (type) {
	case 0:
		return isOnBlock;
		break;
	case 1:
		return isNeedNewBlock;
		break;
	}
}

int Tetris::getPos(int type)
{
	switch (type) {
	case 0:
		return pos.X;
		break;
	case 1:
		return pos.Y;
		break;
	}
}