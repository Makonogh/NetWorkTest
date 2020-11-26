#pragma once
#include <memory>
#include <DxLib.h>
#include <chrono>

class BaseScene;

using uniqueScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	int GetScreenID(void);
	virtual void Init();
	virtual ~BaseScene();
	virtual uniqueScene Update(uniqueScene) = 0;
	virtual void Draw();
	int SceneCount;
private:
	virtual void DrawOwnScreen();
protected:
	int screenID_;
};
