#include "BaseScene.h"

BaseScene::BaseScene()
{
	SceneCount = 0;
}

int BaseScene::GetScreenID(void)
{
	return screenID_;
}

void BaseScene::Init()
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw()
{

}

void BaseScene::DrawOwnScreen()
{
}
