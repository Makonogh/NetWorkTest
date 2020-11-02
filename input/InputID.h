#pragma once
#include <type_traits>

enum class InputID
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BT1,
	BT2,
	BT3,
	BT4,
	MAX
};

static InputID begin(InputID) { return InputID::UP; };
static InputID end(InputID) { return InputID::MAX; };
static InputID operator++ (InputID& state) { return (state = InputID(std::underlying_type<InputID>::type(state) + 1)); };
static InputID operator* (InputID state) { return state; };

