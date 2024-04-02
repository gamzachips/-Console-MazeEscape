#pragma once
#include "pch.h"

enum class Color
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = FOREGROUND_GREEN | RED,
	WHITE = RED | GREEN | BLUE,
};

enum class KeyCode
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,

};

class ConsoleHelper
{
public :
	static void Init();
	static void Update();

	static float GetDeltaTime() { return _deltaTime; }
private:
	//time
	static float _deltaTime;
	static ULONGLONG _prevTime;
	static ULONGLONG _curTime;
};

