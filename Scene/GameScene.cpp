#include "GameScene.h"
#include "../TMX/TMXMng.h"

GameScene::GameScene()
{
	LoadDivGraph("image/map.png", 12, 4, 3, 32, 32, TileSet_);
}

GameScene::~GameScene()
{
}

uniqueScene GameScene::Update(uniqueScene own)
{
	Draw();
	return own;
}

void GameScene::Draw()
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	auto mapData = lpTMXMng.GetMapData();
	for (auto data : mapData)
	{
		for (int y = 0; y < 17; y++)
		{
			for (int x = 0; x < 21; x++)
			{
				if (data.second[y * 21 + x] > 0) {
					DrawGraph(x * 32, y * 32, TileSet_[data.second[y * 21 + x]], true);
				}
			}
		}
	}
	ScreenFlip();
}
