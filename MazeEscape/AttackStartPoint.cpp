#include "pch.h"
#include "AttackStartPoint.h"

void AttackStartPoint::Update()
{
	_timer += ConsoleHelper::GetDeltaTime();
}

bool AttackStartPoint::IsRemoveTime()
{
	if (_timer > _duration)
	{
		return true;
	}
	return false;
}
