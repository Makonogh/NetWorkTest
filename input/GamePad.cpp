#include "GamePad.h"
#include <DxLib.h>

ContType GamePad::GetType(void)
{
	return ContType::GamePad;
}

bool GamePad::Setup(int no)
{
	_connection = GetJoypadNum();
	if (no == 0)
	{
		_id = DX_INPUT_PAD1;
	}
	else
	{
		_id = DX_INPUT_PAD2;
	}
	_inputTbl = {
					{InputID::UP,PAD_INPUT_UP},
					{InputID::DOWN,PAD_INPUT_DOWN},
					{InputID::LEFT,PAD_INPUT_LEFT},
					{InputID::RIGHT,PAD_INPUT_RIGHT},
					{InputID::BT1,PAD_INPUT_1},
					{InputID::BT2,PAD_INPUT_2},
					{InputID::BT4,PAD_INPUT_4}
				};
	return false;
}

bool GamePad::Update(void)
{
	if (GetJoypadNum() != _connection)
	{
		return false;
	}
	_padInput = GetJoypadInputState(_id);
	for (auto id : InputID())
	{
		data_[id][static_cast<int>(Trg::Old)] = data_[id][static_cast<int>(Trg::Now)];
		data_[id][static_cast<int>(Trg::Now)] = _padInput&_inputTbl[id];
	}
	return true;
}

int GamePad::GetID(void)
{
	return _id;
}
