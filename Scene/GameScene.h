#pragma once
#include "BaseScene.h"
#include "../Obj/Obj.h"
#include <vector>

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	uniqueScene Update(uniqueScene own) override;
	void Draw() override;
private:
	int TileSet_[12];
	std::vector<std::shared_ptr<Obj>> ObjList_;
};

