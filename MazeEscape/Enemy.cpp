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
	////���� �ֱ⸶�� ���� �Ǵ� �¿� �̵� 
	
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

		//�÷��̾ �ִ� ��ġ���, �÷��̾� ����� -1
		if (_maze->GetTileType(_position) == TileType::TT_Player)
		{
			_maze->GetPlayer()->GetDamage();
		}
		//���� ����Ʈ�� �ִ� ��ġ��� �� ����� -1
		if (_maze->GetTileType(_position) == TT_AttackPoint)
		{
			GetDamage();
		}
	}
}
