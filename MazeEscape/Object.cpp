#include "pch.h"
#include "Object.h"


Pos Object::GetPosition()
{
	return _position;
}

void Object::SetPosition(Pos pos)
{
	_position = pos;
}

void Object::SetMaze(Maze* maze)
{
	_maze = maze;
}
