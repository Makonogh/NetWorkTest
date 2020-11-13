#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "BaseScene.h"
#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng& GetInstance()
	{
		static std::once_flag once;
		std::call_once(once, Create);
		return (*s_instance);
	}

	static void Create()
	{
		if (s_instance == nullptr)
		{
			s_instance = new SceneMng();
		}
	}

	static void Destroy()
	{
		delete s_instance;
		s_instance = nullptr;
	}
	void Run(void);
private:
	SceneMng();
	~SceneMng();
	void Draw(void);
	bool Init(void);
	void Fps(void);

	uniqueScene _activeScene;
	static SceneMng* s_instance;
	int frameCount_;
	int fpsView_;
	std::chrono::system_clock::time_point start_;
	std::chrono::system_clock::time_point end_;
};

