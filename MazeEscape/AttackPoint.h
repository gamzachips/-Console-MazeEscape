#pragma once
#include "Object.h"

class AttackPoint : public Object
{
public:
	AttackPoint(TileType type) : Object(type) {}
	float GetDuration() { return _duration; }
	void Update();
	bool IsRemoveTime();
private:
	float _duration = 0.5f;
	float _timer = 0.f;

};

