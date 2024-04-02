#pragma once
#include "Maze.h"

class Maze;

class Object
{
public:
	Object(TileType type) : _type(type) {}
	Pos GetPosition();
	TileType GetTileType() { return _type; }
	void SetPosition(Pos pos);
	void SetMaze(Maze* maze);

protected:
	TileType _type = TileType::TT_None;
	Pos _position;
	Maze* _maze = nullptr;
};

