#include "GameScene.h"
#include "../Obj/Player.h"
#include "../Obj/Wall.h"
#include "../Obj/Item.h"
#include "../NetWork/NetWork.h"
#include "../Obj/Generator.h"

GameScene::GameScene()
{
	//画像の読み込み関係

	LoadDivGraph("image/map.png", 12, 4, 3, 32, 32, TileSet_);
	LoadDivGraph("image/fireTest.png", 12, 3, 4, 32, 32, FireSet_);

	// マップデータの取得
	mapData_ = lpTMXMng.GetMapData();
	myID_ = lpNetWork.GetPlayerID().first;
	playerMax_ = lpNetWork.GetPlayerID().second;
	// マップデータから
	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			auto data = mapData_[LAYER::OBJ][y * 21 + x];
			if (data != 0)
			{
				ObjList_.emplace_back(std::make_shared <Wall>(Vector2(32 * x, 32 * y), static_cast<COLOR>(data - 1)));
			}
			data = NULL;
			data = mapData_[LAYER::ITEM][y * 21 + x];
			if (data != 0)
			{
				ItemList_.emplace_back(std::make_shared <Item>(Vector2(32 * x, 32 * y), static_cast<ITEM_TYPE>(data - 1)));
			}

			if (mapData_[LAYER::CHAR][y * 21 + x] == 4 && PlayerList_.size() < playerMax_)
			{
				PlayerList_.emplace_back(std::make_shared <Player>(Vector2(32 * x, 32 * y), *this));
			}
		}
	}
	screenID_ = MakeScreen(32 * 21, 32 * 17, true);
}

GameScene::~GameScene()
{
}

void GameScene::SetBomb()
{
}

void GameScene::SetGene(Vector2 tipos)
{
	ObjList_.emplace_back(std::make_shared <Generator>(tipos, *this));
}

std::list<std::shared_ptr<Obj>> GameScene::GetObj()
{
	return ObjList_;
}
uniqueScene GameScene::Update(uniqueScene own)
{
	for (auto& data : ObjList_)
	{
		data->Update();
	}
	for (auto& data : PlayerList_)
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
				DrawGraph(x * 32, y * 32, TileSet_[mapData_[LAYER::BG][y * 21 + x] - 1], true);
			}
		}
	}

	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			if (mapData_[LAYER::BOMB][y * 21 + x] == 1)
			{
				DrawGraph(x * 32, y * 32, FireSet_[mapData_[LAYER::BOMB][y * 21 + x] - 1], true);
			}
		}
	}

	for (auto& data : ObjList_)
	{
		data->Draw(TileSet_);
	}

	for (auto& data : ItemList_)
	{
		data->Draw(TileSet_);
	}

	for (auto& data : PlayerList_)
	{
		data->Draw();
	}
}

std::vector<unsigned  char>& GameScene::GetMapData_(LAYER layer_)
{
	return mapData_[layer_];
}

std::pair<unsigned int, unsigned int> GameScene::GetID()
{
	return { myID_,playerMax_ };
}
