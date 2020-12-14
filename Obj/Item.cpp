#include "Item.h"

Item::Item(Vector2 pos, ITEM_TYPE item)
{
	pos_ = pos;
	size_ = { 32,32 };
	item_ = item;
	type_ = OBJ_TYPE::ITEM;
	tilePos_ = pos / 32;
}

void Item::Draw(int* TileImg)
{
	DrawGraph(pos_.x, pos_.y, TileImg[static_cast<int>(item_)], true);
}

Item::~Item()
{
}
