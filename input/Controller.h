#pragma once
#include <map>
#include <utility>
#include <array>
#include "InputID.h"

enum class ContType
{
	GamePad,
	KeyBoard,
	Mouse,
	Max
};


enum class Trg
{
	Now,
	Old,
	MAX
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::MAX) >;
using CntData = std::map<InputID, TrgBool>;

struct Controller
{
	void operator() ()
	{
		Update();
	}
	const CntData& GetCntData(void)
	{
		return data_;
	}
	virtual ContType GetType(void) = 0;
	virtual bool Setup(int no) = 0;
	virtual int GetID(void) = 0;
private:
	virtual bool Update(void) = 0;
protected:
	CntData data_;
};

