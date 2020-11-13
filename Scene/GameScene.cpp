#include "GameScene.h"
#include "../Obj/Char.h"
#include "../Obj/Wall.h"
#include "../NetWork/NetWork.h"

GameScene::GameScene()
{
	//画像の読み込み関係

	LoadDivGraph("image/map.png", 12, 4, 3, 32, 32, TileSet_);

	// マップデータの取得
	mapData_ = lpTMXMng.GetMapData();

	// マップデータから
	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			auto data = mapData_[LAYER::OBJ][y * 21 + x];
			if (data != 0)
			{
				ObjList_.emplace_back(std::make_shared <Wall>(Vector2(32 * x,32 * y),static_cast<COLOR>(data)));
			}
		
			if (mapData_[LAYER::CHAR][y * 21 + x] + 1 != 0)
			{
				CharList_.emplace_back(std::make_shared <Char>(Vector2(32 * x, 32 * y)));
			}
		}
	}

	screenID_ = MakeScreen(32 * 21 , 32 * 17,true);
}

GameScene::~GameScene()
{
}

uniqueScene GameScene::Update(uniqueScene own)
{
	for (auto data : CharList_)
	{
		data->Update();
	}
	Draw();
	return own;
}

void GameScene::Draw()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	
	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			if (mapData_[LAYER::BG][y * 21 + x] > 0) 
			{
				DrawGraph(x * 32, y * 32, TileSet_[mapData_[LAYER::BG][y * 21 + x]], true);
			}
		}
	}

	for (auto data : ObjList_)
	{
		data->Draw(TileSet_);
	}

	for (auto data : CharList_)
	{
		data->Draw();
	}
}
