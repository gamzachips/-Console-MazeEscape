#include "pch.h"
#include "Maze.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "List.h"
#include "AttackPoint.h"
#include "AttackStartPoint.h"
using namespace std;


const char* TILE = "■";
const char* EMPTY = "  ";
const char* PLAYER = "★";
const char* ENEMY = "※";
const char* HPITEM = "♥";
const char* VISIONITEM = "◈";
const char* ATTACKSTART = "●";
const char* ATTACKPOINT = "○";
const char* EXIT = "♣";

Maze::Maze()
{

}

Maze::~Maze()
{
	delete _player;
	_enemies.clear();
	_attackPoints.clear();
	delete _attackStartPoint;
}

void Maze::Init()
{
	for (int y = 0; y < mazeSize; y++)
	{
		for (int x = 0; x < mazeSize; x++)
		{
			//초기 미로 셋팅을 가지고 객체들을 생성한다. 

			switch (_tiles[y][x])
			{
				case TileType::TT_Player:
				{
					_player = new Player;
					_player->SetPosition(Pos(y, x));
					_player->SetMaze(this);
					UI::SetPlayer(_player);
					break;
				}
				case TileType::TT_VerticalEnemy:
				{
					VerticalEnemy* enemy = new VerticalEnemy;
					enemy->SetPosition(Pos(y, x));
					enemy->SetMaze(this);
					_enemies.push_back(enemy);
					break;
				}
				case TileType::TT_HorizontalEnemy:
				{
					HorizontalEnemy* enemy = new HorizontalEnemy;
					enemy->SetPosition(Pos(y, x));
					enemy->SetMaze(this);
					_enemies.push_back(enemy);
					break;
				}
			}
		}
	}
}

void Maze::Update()
{
	if (_player != nullptr)
		_player->Update();

	if(_attackStartPoint != nullptr)
		_attackStartPoint->Update();

	for (List<Enemy*>::iterator it = _enemies.begin(); it != _enemies.end();)
	{
		(*it)->Update();

		//죽었으면 제거
		if ((*it)->GetHP() <= 0)
		{
			_tiles[(*it)->GetPosition()._y][(*it)->GetPosition()._x] = TT_Empty;
			it = _enemies.erase(it);
		}
		else
			++it;
	}

	//공격
	{
		if (_attackStartPoint != nullptr)
		{
			MakeAttacks();
		}
	}

	for (List<AttackPoint*>::iterator it = _attackPoints.begin(); it != _attackPoints.end(); )
	{
		(*it)->Update();

		//공격 포인트 일정 시간 지나면 제거
		if ((*it)->IsRemoveTime())
		{
			Pos attackPos = (*it)->GetPosition();
			_tiles[attackPos._y][attackPos._x] = TT_Empty;
			it = _attackPoints.erase(it);
		}
		else
			++it;
	}
}

void Maze::WriteMaze()
{
	int visionRange = _player->GetVisionRange();
	int yStart = max(0, _player->GetPosition()._y - visionRange);
	int yEnd = min(mazeSize-1, _player->GetPosition()._y + visionRange);
	int xStart = max(0, _player->GetPosition()._x - visionRange);
	int xEnd = min(mazeSize-1, _player->GetPosition()._x + visionRange);

	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	ConsoleRenderer::AddNewLine();
	for (int y = yStart; y <= yEnd; y++)
	{
		ConsoleRenderer::SetString("                    ", (WORD)Color::WHITE);
		for (int x = xStart; x <= xEnd; x++)
		{
			switch (_tiles[y][x])
			{
				case TileType::TT_Empty:
					ConsoleRenderer::SetString(EMPTY, (WORD)Color::WHITE);
					break;
				case TileType::TT_Wall:
					ConsoleRenderer::SetString(TILE, (WORD)Color::WHITE);
					break;
				case TileType::TT_AttackStart:
					ConsoleRenderer::SetString(ATTACKSTART, (WORD)Color::CYAN);
					break;
				case TileType::TT_AttackPoint:
					ConsoleRenderer::SetString(ATTACKPOINT, (WORD)Color::CYAN);
					break;
				case TileType::TT_Player:
					ConsoleRenderer::SetString(PLAYER, (WORD)Color::GREEN);
					break;
				case TileType::TT_VerticalEnemy: 
					ConsoleRenderer::SetString(ENEMY, (WORD)Color::YELLOW);
					break;
				case TileType::TT_HorizontalEnemy:
					ConsoleRenderer::SetString(ENEMY, (WORD)Color::YELLOW);
					break;
				case TileType::TT_HPItem:
					ConsoleRenderer::SetString(HPITEM, (WORD)Color::RED);
					break;
				case TileType::TT_VisionRangeItem:
					ConsoleRenderer::SetString(VISIONITEM, (WORD)Color::MAGENTA);
					break;				
				case TileType::TT_Exit:
					ConsoleRenderer::SetString(EXIT, (WORD)Color::BLUE);
					break;
			}
		}
		ConsoleRenderer::AddNewLine();
	}
}

void Maze::SetTiles()
{
	//Player
	{
		if (_player != nullptr)
		{
			Pos playerPos = _player->GetPosition();
			_tiles[playerPos._y][playerPos._x] = TT_Player;
		}
	}
	
	//Enemies
	{
		for (List<Enemy*>::iterator it = _enemies.begin(); it != _enemies.end(); ++it)
		{
			Pos pos = (*it)->GetPosition();
			_tiles[pos._y][pos._x] = (*it)->GetTileType();
		}
	}
	
	//AttackPoints
	{
		for (List<AttackPoint*>::iterator it = _attackPoints.begin(); it != _attackPoints.end(); ++it)
		{
			Pos pos = (*it)->GetPosition();
			_tiles[pos._y][pos._x] = (*it)->GetTileType();
		}
	}
	//AttackStartPoint
	{
		if (_attackStartPoint != nullptr)
		{
			Pos attackPos = _attackStartPoint->GetPosition();
			_tiles[attackPos._y][attackPos._x] = TT_AttackStart;
		}
	}

}

int Maze::GetTileType(Pos pos)
{
	if (pos._x < 0 || pos._x >= mazeSize) return TT_None;
	if (pos._y < 0 || pos._y >= mazeSize) return TT_None;

	int  ret = _tiles[pos._y][pos._x];
	return ret;
}

void Maze::SetTileType(Pos pos, TileType type)
{
	_tiles[pos._y][pos._x] = type;
}

void Maze::RemoveTile(Pos pos)
{
	_tiles[pos._y][pos._x] = TT_Empty;
}

void Maze::MakeAttackPoint(Pos pos)
{
	//벽이 아니라면 공격대상
	if (_tiles[pos._y][pos._x] != TT_Wall)
	{
		//공격 포인트 생성
		AttackPoint* point = new AttackPoint(TT_AttackPoint);
		point->SetPosition(pos);
		_attackPoints.push_back(point);

		//공격 포인트 생성할 위치에 플레이어가 있으면 대미지
		if (pos == _player->GetPosition())
		{
			_player->GetDamage();
		}
		
		//공격 포인트 생성할 위치에 적이 있으면 대미지
		for (List<Enemy*>::iterator it = _enemies.begin(); it != _enemies.end(); ++it)
		{
			if (pos == (*it)->GetPosition())
			{
				(*it)->GetDamage();
			}
		}
	}
}

void Maze::SetAttackStart(Pos pos)
{
	_attackStartPoint = new AttackStartPoint(TT_AttackStart);
	_attackStartPoint->SetPosition(pos);
}

void Maze::MakeAttacks()
{
	if (_attackStartPoint->IsRemoveTime())
	{
		int dy[4] = { -1, 0, 1, 0 };
		int dx[4] = { 0, 1, 0, -1 };

		//공격 포인트 중심으로 상하좌우 공격
		MakeAttackPoint(_attackStartPoint->GetPosition());
		for (int i = 0; i < 4; i++)
		{
			Pos pos;
			pos._y = _attackStartPoint->GetPosition()._y + dy[i];
			pos._x = _attackStartPoint->GetPosition()._x + dx[i];
			MakeAttackPoint(pos);
		}
		_player->SetIsAttacking(false);

		//공격 시작 포인트 삭제
		_attackStartPoint = nullptr;
		delete _attackStartPoint;
	}
	
}

bool Maze::CheckGameClear()
{
	if (GetTileType(_player->GetPosition()) == TT_Exit)
		return true;
	return false;
}

bool Maze::CheckPlayerDead()
{
	return _player->GetHP() <= 0;
}
