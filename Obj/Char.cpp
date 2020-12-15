#include "Char.h"
#include "DxLib.h"
#include "..//Scene/GameScene.h"
#include <algorithm>

int Char::charID_;


Char::Char(Vector2 pos, BaseScene& scene) :scene_(scene)
{
	pos_ = pos;
	size_ = { CHAR_SIZE_X,CHAR_SIZE_Y };
	tilePos_ = pos_ / 32;
	type_ = OBJ_TYPE::CHAR;

	LoadDivGraph("image/bomberman1.png", 20, 5, 4, 32, 205 / 4, Image);
	if (charID_ % 2)
	{
		dir_ = DIR::LEFT;
	}
	else
	{
		dir_ = DIR::RIGHT;
	}
	dir_ = static_cast<DIR>((charID_ / 5) % 4);
	AnimFrame = 0;
	Frame = 0;
	charID_++;
}

void Char::Draw()
{
	DrawBox(tilePos_.x * 32, tilePos_.y * 32, tilePos_.x * 32 + 32, tilePos_.y * 32 + 32, 0x00ff00, false);
	DrawGraph(pos_.x, pos_.y - 25, Image[static_cast<int>(dir_) + AnimFrame / 10 % 4 * 5], true);
}

void Char::UpdateDef()
{
	auto pos = pos_;
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	{
		KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_UP, Frame);
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	{
		KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_DOWN, Frame);
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	{
		KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_RIGHT, Frame);
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	{
		KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_LEFT, Frame);
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1)
	{
		dynamic_cast<GameScene&>(scene_).SetGene(tilePos_);
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	{
		pos.y -= 4;
		tilePos_.y = (pos.y) / 32;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	{
		pos.y += 4;
		tilePos_.y = (pos.y + 30) / 32;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	{
		pos.x += 4;
		tilePos_.x = (pos.x + 32) / 32;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	{
		pos.x -= 4;
		tilePos_.x = (pos.x) / 32;
	}

	auto moveFlag = true;
	for (auto& data : dynamic_cast<GameScene&>(scene_).GetObj())
	{
		if (data->GetType() == OBJ_TYPE::WALL)
		{
			if (tilePos_ == data->GetTilePos())
			{
				moveFlag = false;
			}
		}
	}
	if (moveFlag)
	{
		pos_ = pos;
	}

	tilePos_ = { (pos_.x + 16) / 32,(pos_.y + 14) / 32 };

	Frame++;
}

void Char::UpdateAuto()
{
}

void Char::UpdateNet()
{
}

int Char::GetID()
{
	return charID_;
}

Char::~Char()
{
}
