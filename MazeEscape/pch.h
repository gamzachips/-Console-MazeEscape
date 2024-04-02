#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "ConsoleHelper.h"
#include "ConsoleRenderer.h"

const int mazeSize = 27;

class Pos
{
public:
	Pos() {}
	Pos(int y, int x) : _x(x), _y(y) {}

	bool operator==(const Pos other)
	{
		if (_x == other._x && _y == other._y)
			return true;
		return false;
	}

	bool operator!=(const Pos other)
	{
		return !(*this == other);
	}

	int _x = 0;
	int _y = 0;
};


enum TileType
{
	TT_Empty = 0,
	TT_Wall = 1,
	TT_VisionRangeItem = 2,
	TT_HPItem = 3,
	TT_Player = 4,
	TT_VerticalEnemy = 5,
	TT_HorizontalEnemy = 6,
	TT_AttackStart = 7,
	TT_AttackPoint = 8,
	TT_None = 9
};