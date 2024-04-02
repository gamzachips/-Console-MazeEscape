#include "pch.h"
#include "AttackPoint.h"

void AttackPoint::Update()
{
	_timer += ConsoleHelper::GetDeltaTime();
	

}

bool AttackPoint::IsRemoveTime()
{
	if (_timer > _duration)
	{
		_timer = 0;
		return true;
	}
	return false;
}
