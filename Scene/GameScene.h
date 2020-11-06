#pragma once
#include "BaseScene.h"
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	void Draw();
private:
	int TileSet[12];
};

