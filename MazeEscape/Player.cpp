#include "pch.h"
#include "Player.h"
#include "Maze.h"


Player::Player() : Creature(TileType::TT_Player)
{
	_hp = 5;
}

void Player::Update()
{
	Input();
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
	if (_maze->GetTileType(nextPos) == TT_AttackPoint)
	{
		//공격 포인트로 이동하려고 하면 대미지
		GetDamage();
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
