#include "pch.h"
#include "Creature.h"

Creature::Creature(TileType type) : Object(type)
{
	
}

void Creature::GetDamage()
{
	_hp = max(0, _hp - 1);
}