#include "Wall.h"
#include "DxLib.h"

Wall::Wall(Vector2 pos, COLOR color)
{
	pos_ = pos;
	size_ = { 32,32 };
	color_ = color;
	type_ = OBJ_TYPE::WALL;
	tilePos_ = pos / 32;
}

void Wall::Draw(int *TileImg)
{
	DrawGraph(pos_.x, pos_.y, TileImg[static_cast<int>(color_)], true);
}

Wall::~Wall()
{
}