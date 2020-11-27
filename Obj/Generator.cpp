#include "Generator.h"
#include "..//Scene/GameScene.h"

Generator::Generator(Vector2 tipos, BaseScene& scene):scene_(scene)
{
	ExpLength_ = EXP_LEN_DEF + 0;				// 0 -> アイテムの数により変動
	NowLength_ = 0;
	pos_ = tipos * 32;
	tilePos_ = tipos;
	frame_ = 0;
	type_ = OBJ_TYPE::GENE;
}

void Generator::Update()
{	
	std::vector<int> &map = dynamic_cast<GameScene&>(scene_).GetMapData_(LAYER::BOMB);
	map[tilePos_.x + tilePos_.y * 21] = static_cast<int>(EXP_TYPE::GZ) * 10 + 0;				// 二桁の数を格納　二桁目はexpType 一桁目はアニメーション
	NowLength_++;

	if (frame_ % 10 == 0)
	{
		
	}
	
	frame_++;
}

Generator::~Generator()
{
}
