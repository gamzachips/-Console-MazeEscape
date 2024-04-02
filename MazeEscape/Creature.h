#include "pch.h"
#include "Object.h"
#pragma once

class Creature : public Object
{
public:
	Creature(TileType type);

	void GetDamage();
	int GetHP() { return _hp; }
	
protected:
	int _hp;
};

