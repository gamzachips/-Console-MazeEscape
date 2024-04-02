#include "pch.h"
#include "Player.h"
#include "Maze.h"


Player::Player() : Creature(TileType::TT_Player)
{
	_maxHp = 5;
	_hp = 5;
}

void Player::Update()
{
	Input();

	if (_visionExpanded)
	{
		_visionTimer += ConsoleHelper::GetDeltaTime();
		if (_visionTimer > _visionItemPersistTime)
		{
			_visionExpanded = false;
			_visionTimer = 0.f;
			_visionRange = 2;
		}
	}
}

void Player::Input()
{
	//키 입력받아 이동
	if (_kbhit() > 0)
	{
		int key = _getch();

		Pos nextPos(_position);
		switch (key)
		{
		case (int)KeyCode::DOWN:
			nextPos._y += 1;
			break;
		case (int)KeyCode::UP:
			nextPos._y -= 1;
			break;
		case (int)KeyCode::LEFT:
			nextPos._x -= 1;
			break;
		case (int)KeyCode::RIGHT:
			nextPos._x += 1;
			break;
		case (int)KeyCode::SPACE:
			StartAttack();
			break;
		}

		if (_position != nextPos)
		{
			_maze->RemoveTile(Pos(_position._y, _position._x));
			Move(nextPos);
		}

	}
}

void Player::Move(Pos nextPos)
{
	if (nextPos._x < 0 || nextPos._x >= mazeSize) return;
	if (nextPos._y < 0 || nextPos._y >= mazeSize) return;
	if (_maze->GetTileType(nextPos) == (int)TileType::TT_Wall)
		return;

	if (_maze->GetTileType(nextPos) == TileType::TT_VerticalEnemy
		|| _maze->GetTileType(nextPos) == TileType::TT_HorizontalEnemy)
	{
		//적이 위치한 곳에 이동하려고 하면 대미지
		GetDamage();
	}
	else if (_maze->GetTileType(nextPos) == TT_AttackPoint)
	{
		//공격 포인트로 이동하려고 하면 대미지
		GetDamage();
	}
	else if (_maze->GetTileType(nextPos) == TT_HPItem)
	{
		//HP아이템 먹으면 HP 1 증가
		_hp = min(_hp + 1, _maxHp);
	}
	else if (_maze->GetTileType(nextPos) == TT_VisionRangeItem)
	{
		//시야증가 아이템 먹으면 시야 3으로 증가
		_visionRange = 3;
		_visionExpanded = true;
	}

	_position = nextPos;
}

void Player::StartAttack()
{
	if (_attacking) return;

	_attacking = true;
	//공격 시작 포인트 생성
	_maze->SetAttackStart(_position);
}

int Player::GetVisionRange()
{
	return _visionRange;
}
