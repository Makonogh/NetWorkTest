#include "Bomb.h"

Bomb::Bomb(Vector2 pos, int length, std::chrono::system_clock::time_point time)
{
	type_ = OBJ_TYPE::BOMB;
	size_ = { 32,32 };
	pos_ = pos;
	length_ = length;
	tilePos_ = pos / 32;
	LoadDivGraph("image/bomb.png", 14, 2, 7, 32, 32, image_);
}

void Bomb::Draw(int* TileImg)
{
	DrawGraph(tilePos_.x * 32, tilePos_.y * 32, image_[0], true);
}

Bomb::~Bomb()
{
}
