#pragma once
#include "Item.h"
class HPItem : public Item
{
public:
	HPItem() : Item(TileType::TT_HPItem) {}
};

