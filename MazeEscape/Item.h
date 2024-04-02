#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(TileType type) : Object(type)
	{}
};

