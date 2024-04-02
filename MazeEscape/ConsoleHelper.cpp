#include "pch.h"
#include "ConsoleHelper.h"
#include "Player.h"

float ConsoleHelper::_deltaTime = 0.0f;
ULONGLONG ConsoleHelper::_prevTime = 0;
ULONGLONG ConsoleHelper::_curTime = 0;


void ConsoleHelper::Init()
{
	_prevTime = _curTime = GetTickCount64();	
}

void ConsoleHelper::Update()
{
	_prevTime = _curTime;
	_curTime = GetTickCount64();
	_deltaTime = (_curTime - _prevTime) / 1000.f;
}
