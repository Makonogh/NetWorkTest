#include "Bomb.h"

Bomb::Bomb(Vector2 pos, int color)
{
	type_ = OBJ_TYPE::BOMB;
	size_ = { 32,32 };
	pos_ = pos;
	length;
	tilePos_ = pos / 32;
}

void Bomb::Draw(int* TileImg)
{
	DrawGraph(pos_.x, pos_.y, TileImg[3], true);
}

Bomb::~Bomb()
{
}
