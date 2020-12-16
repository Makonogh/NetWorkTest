#include "Player.h"
#include "Char.h"
#include "DxLib.h"
#include "..//Scene/GameScene.h"
#include "..//NetWork/NetWork.h"
#include <algorithm>

unsigned int Player::charID_ = -5;

Player::Player(Vector2 pos, BaseScene& scene) :scene_(scene)
{
	pos_ = pos;
	size_ = { CHAR_SIZE_X,CHAR_SIZE_Y };
	tilePos_ = pos_ / 32;
	type_ = OBJ_TYPE::CHAR;
	charID_ += 5;

	LoadDivGraph("image/bomberman1.png", 20, 5, 4, 32, 205 / 4, Image);
	if (charID_ % 2)
	{
		dir_ = DIR::LEFT;
	}
	else
	{
		dir_ = DIR::RIGHT;
	}
	AnimFrame = 0;
	Frame = 0;
	
	if (charID_ == dynamic_cast<GameScene&>(scene_).GetID().first)
	{
		playType_ = PLAY_TYPE::OPE;

		updFunc_ = std::bind(&Player::UpdateOpe, this);
	}
	else
	{
		playType_ = PLAY_TYPE::REV;
		updFunc_ = std::bind(&Player::UpdateRev, this);
	}
}

void Player::Draw()
{
	if (playType_ == PLAY_TYPE::OPE) {
		DrawBox(tilePos_.x * 32, tilePos_.y * 32, tilePos_.x * 32 + 32, tilePos_.y * 32 + 32, 0x00ff00, false);
	}
	DrawGraph(pos_.x, pos_.y - 25, Image[static_cast<int>(dir_) + AnimFrame / 10 % 4 * 5], true);
	AnimFrame++;
}

void Player::Update()
{
	updFunc_();
	Frame++;
}

void Player::UpdateOpe()
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
		dir_ = DIR::UP;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	{
		pos.y += 4;
		tilePos_.y = (pos.y + 30) / 32;
		dir_ = DIR::DOWN;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	{
		pos.x += 4;
		tilePos_.x = (pos.x + 32) / 32;
		dir_ = DIR::RIGHT;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	{
		pos.x -= 4;
		tilePos_.x = (pos.x) / 32;
		dir_ = DIR::LEFT;
	}

	auto moveFlag = true;
	if (CheckHitKey(KEY_INPUT_TAB) == false)
	{
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
	}
	if (moveFlag)
	{
		pos_ = pos;
	}

	tilePos_ = { (pos_.x + 16) / 32,(pos_.y + 14) / 32 };

	MesPacket sendData;
	unionData data[4] = {};
	data[0].iData = charID_;
	data[1].iData = pos_.x;
	data[2].iData = pos_.y;
	data[3].iData = static_cast<unsigned int> (dir_);

	sendData = { data[0], data[1],data[2],data[3] };
	lpNetWork.SendAllMes(MesType::POS, sendData);
}

void Player::UpdateAuto()
{
}

void Player::UpdateRev()
{
}


int Player::GetID()
{
	return charID_;
}

Player::~Player()
{
}
