#include "Obj.h"

Obj::Obj()
{
	tilePos_ = pos_ / 32; 
}

Vector2 Obj::GetPos()
{
	return pos_;
}

Vector2 Obj::GetTilePos()
{
	return tilePos_;
}

OBJ_TYPE Obj::GetType()
{
	return type_;
}

void Obj::Draw()
{
}

void Obj::Draw(int* TileImg)
{
}

void Obj::Update()
{
}

void Obj::UpdateOpe()
{
}

void Obj::UpdateAuto()
{
}

void Obj::UpdateRev()
{
}

Obj::~Obj()
{
}
