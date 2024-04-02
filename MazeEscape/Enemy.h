#pragma once
#include "Creature.h"

class Enemy : public Creature
{
public:

	Enemy(TileType type);

	void Update();
protected:
	float _timer = 0.f;
	float _movingPeriod = 0.5f;

	int _moving[5] = {-1, -1, 1, 1};
	int _moveIndex = 1; 
	bool _verticalMove = true;
};

class VerticalEnemy : public Enemy
{
public:
	VerticalEnemy() : Enemy(TileType::TT_VerticalEnemy)
	{
		_verticalMove = true;
	}
};

class HorizontalEnemy : public Enemy
{
public:
	HorizontalEnemy() : Enemy(TileType::TT_HorizontalEnemy)
	{
		_verticalMove = false;
	}
};