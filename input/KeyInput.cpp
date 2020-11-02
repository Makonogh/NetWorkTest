#include "DxLib.h"
#include "KeyInput.h"

ContType KeyInput::GetType(void)
{
    return ContType::KeyBoard;
}

bool KeyInput::Setup(int no)
{
    if (no == 0)
    {
        inputTbl_ = {
            {InputID::UP,KEY_INPUT_W},
            {InputID::DOWN,KEY_INPUT_S},
            {InputID::LEFT,KEY_INPUT_A},
            {InputID::RIGHT,KEY_INPUT_D},
            {InputID::BT1,KEY_INPUT_E},
            {InputID::BT2,KEY_INPUT_Q},
            {InputID::BT3,KEY_INPUT_SPACE},
            {InputID::BT4,KEY_INPUT_P}
        };
    }
    else
    {
        inputTbl_ = {
            {InputID::UP,KEY_INPUT_NUMPAD8},
            {InputID::DOWN,KEY_INPUT_NUMPAD5},
            {InputID::LEFT,KEY_INPUT_NUMPAD4},
            {InputID::RIGHT,KEY_INPUT_NUMPAD6},
            {InputID::BT1,KEY_INPUT_NUMPAD9},
            {InputID::BT2,KEY_INPUT_NUMPAD7},
            {InputID::BT3,KEY_INPUT_NUMPADENTER},
            {InputID::BT4,KEY_INPUT_L}
        };
    }

    return true;
}

bool KeyInput::Update(void)
{
    GetHitKeyStateAll(keyData_.data());
    for (auto id : InputID())
    {
        data_[id][static_cast<int>(Trg::Old)] = data_[id][static_cast<int>(Trg::Now)];
        data_[id][static_cast<int>(Trg::Now)] = keyData_[inputTbl_[id]];
    }
    return true;
}

int KeyInput::GetID(void)
{
    return 0;
}
