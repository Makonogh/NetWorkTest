#include "SceneMng.h"
#include "LoginScene.h"
#include "GameScene.h"
#include "../_debug/_DebugDispOut.h"
#include <DxLib.h>

SceneMng* SceneMng::s_instance = nullptr;

std::chrono::system_clock::time_point SceneMng::GetTime()
{
	return end_;
}

void SceneMng::Run(void)
{
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	
		Fps();
		Draw();
	}
}

SceneMng::SceneMng()
{
	SetDoubleStartValidFlag(TRUE);
	Init();
}

SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawGraph(0,0,_activeScene->GetScreenID(),true);
	_dbgDrawFormatString(32, 32 * 15 + 8, 0xffff00, "1/%d", fpsView_);
	ScreenFlip();
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
	start_ = std::chrono::system_clock::now();
	SetAlwaysRunFlag(true);
	return true;
}

void SceneMng::Fps(void)
{
	end_ = std::chrono::system_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count() >= 1000)
	{
		fpsView_ = frameCount_;
		frameCount_ = 0;
		start_ = end_;
	}
	else
	{
		frameCount_++;
	}
}
