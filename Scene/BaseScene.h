#pragma once
#include <memory>
#include <DxLib.h>

class BaseScene;

using uniqueScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual void init();
	virtual ~BaseScene();
	virtual uniqueScene Update(uniqueScene) = 0;
	virtual void Draw();
	int SceneCount;
private:
	int screenID_;
};
