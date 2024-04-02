#include "pch.h"
#include "Enemy.h"
#include "Maze.h"
#include "Player.h"

Enemy::Enemy(TileType type) : Creature(type)
{
	_hp = 1;
}

void Enemy::Update()
{ 
	////일정 주기마다 상하 또는 좌우 이동 
	
	_timer += ConsoleHelper::GetDeltaTime();
	if (_timer > _movingPeriod)
	{
		_timer -= _movingPeriod;

		_moveIndex = (_moveIndex + 1) % 5;

		_maze->RemoveTile(_position);

		if (_verticalMove)
			_position._y += _moving[_moveIndex];
		else
			_position._x += _moving[_moveIndex];

		//플레이어가 있는 위치라면, 플레이어 대미지 -1
		if (_maze->GetTileType(_position) == TileType::TT_Player)
		{
			_maze->GetPlayer()->GetDamage();
		}
		//공격 포인트가 있는 위치라면 적 대미지 -1
		if (_maze->GetTileType(_position) == TT_AttackPoint)
		{
			GetDamage();
		}
	}
}
