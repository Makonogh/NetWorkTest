#include "SceneMng.h"
#include "LoginScene.h"
#include "GameScene.h"
#include <DxLib.h>

SceneMng* SceneMng::s_instance = nullptr;

void SceneMng::Run(void)
{
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();
	}
}

SceneMng::SceneMng()
{
	Init();
}

SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
}

bool SceneMng::Init(void)
{
	SetGraphMode(32 * 21, 32 * 17, 16);
	ChangeWindowMode(true);
	SetWindowText("É{ÉìÉoÅ[");
	SetDrawScreen(DX_SCREEN_BACK);						//  ﬁØ∏ ﬁØÃßÇ…ê›íË
	if (DxLib_Init() == -1)
	{
		return false;
	}
	_activeScene = std::make_unique<LoginScene>();
	return false;
}
