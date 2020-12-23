#include "Player.h"
#include "Char.h"
#include "DxLib.h"
#include "..//Scene/GameScene.h"
#include "..//Scene/SceneMng.h"
#include "..//NetWork/NetWork.h"
#include <algorithm>

unsigned int Player::charID_ = 0;

Player::Player(Vector2 pos, BaseScene& scene) :scene_(scene)
{
	pos_ = pos;
	size_ = { CHAR_SIZE_X,CHAR_SIZE_Y };
	tilePos_ = pos_ / 32;
	type_ = OBJ_TYPE::CHAR;
	myID_ = charID_;
	charID_ += 5;
	DethFlag_ = false;

	old = 0;
	now = 0;

	LoadDivGraph("image/bomberman1.png", 20, 5, 4, 32, 205 / 4, Image_);
	dir_ = static_cast<DIR>(myID_ % 4 + 1);
	AnimFrame_ = 0;
	Frame_ = 0;

	if (myID_ == dynamic_cast<GameScene&>(scene_).GetID().first)
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
		DrawBox(pos_.x, pos_.y, pos_.x + 32,pos_.y + 32, 0x00ff00, false);
	}
	DrawGraph(pos_.x, pos_.y - 25, Image_[static_cast<int>(dir_) + AnimFrame_ / 10 % 4 * 5], true);
	AnimFrame_++;
}

void Player::Update()
{
	updFunc_();
	Frame_++;
}

void Player::UpdateOpe()
{
	auto pos = pos_;
	//if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
	//{
	//	KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_UP, Frame_);
	//}
	//if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
	//{
	//	KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_DOWN, Frame_);
	//}
	//if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	//{
	//	KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_RIGHT, Frame_);
	//}
	//if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	//{
	//	KeyLog.emplace_back((DX_INPUT_KEY_PAD1)&PAD_INPUT_LEFT, Frame_);
	//}
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
		tilePos_.y = (pos.y + 32) / 32;
		dir_ = DIR::DOWN;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
	{
		pos.x += 4;
		tilePos_.x = (pos.x + 30) / 32;
		dir_ = DIR::RIGHT;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
	{
		pos.x -= 4;
		tilePos_.x = (pos.x) / 32;
		dir_ = DIR::LEFT;
	}
	if (CheckHitKey(KEY_INPUT_L))
	{
		DethFlag_ = true;	
	}



	auto moveFlag = true;
	if (CheckHitKey(KEY_INPUT_TAB) == false)
	{
		for (auto& data : dynamic_cast<GameScene&>(scene_).GetObj())
		{
			if (data->GetType() == OBJ_TYPE::WALL || data->GetType()== OBJ_TYPE::BOMB)
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

	old = now;
	now = CheckHitKey(KEY_INPUT_K);
	if (!old && now)
	{
		MesPacket sendData;
		unionData data[7] = {};
		data[0].iData = myID_;
		data[1].iData = myID_ + 1;
		data[2].iData = pos_.x;
		data[3].iData = pos_.y;
		data[4].iData = 3;
		auto t = (lpSceneMng.GetTime());
		auto time = t.time_since_epoch();
		auto value = std::chrono::duration_cast<std::chrono::milliseconds>(time);
		long long ti = value.count();

		data[5].iData = static_cast<int> (ti >> 8);
		data[6].iData = static_cast<int> (ti);

		sendData = { data[0], data[1],data[2],data[3] ,data[4] ,data[5] ,data[6] };
		lpNetWork.SendAllMes(MesType::SET_BOMB, sendData);

		dynamic_cast<GameScene&>(scene_).SetBomb(tilePos_ * 32, 3);
	}

	MesPacket sendData;
	unionData data[4] = {};
	data[0].iData = myID_;
	data[1].iData = pos_.x;
	data[2].iData = pos_.y;
	data[3].iData = static_cast<unsigned int> (dir_);

	sendData = { data[0], data[1],data[2],data[3] };
	lpNetWork.SendAllMes(MesType::POS, sendData);
	if (DethFlag_)
	{
		MesPacket data;
		data.emplace_back(unionData{ myID_ });
		lpNetWork.SendAllMes(MesType::DETH, data);
	}
}

void Player::UpdateAuto()
{
}

void Player::UpdateRev()
{
	auto data = lpNetWork.GetPosData(myID_);
	if (data[2] != -1)
	{
		pos_.x = data[0];
		pos_.y = data[1];
		dir_ = static_cast<DIR> (data[2]);
	}
}

bool Player::GetFlag()
{
	return DethFlag_;
}


int Player::GetID()
{
	return charID_;
}

Player::~Player()
{
}
