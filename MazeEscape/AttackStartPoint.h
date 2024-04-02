#pragma once
#include "Object.h"
class AttackStartPoint : public Object
{
public:
	AttackStartPoint(TileType type) : Object(type) {}
	float GetDuration() { return _duration; }
	void Update();
	bool IsRemoveTime();
private:
	float _duration = 1.f;
	float _timer = 0.f;
};

