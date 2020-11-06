#include "GameScene.h"
#include "../TMX/TMXMng.h"

GameScene::GameScene()
{
	LoadDivGraph("image/map.png", 12, 4, 3, 32, 32, TileSet);
}

GameScene::~GameScene()
{
}

void GameScene::Draw()
{
	auto mapData = lpTMXMng.GetMapData();
	for (auto data : mapData)
	{
		for (int y = 0; y < 17; y++)
		{
			for (int x = 0; x < 21; x++)
			{
				if (data.second[y * 21 + x] > 0) {
					DrawGraph(x * 32, y * 32, TileSet[data.second[y * 21 + x]], true);
				}
			}
		}
	}
}
