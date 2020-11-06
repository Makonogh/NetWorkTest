#pragma once
#include "BaseScene.h"
#include "../NetWork/NetWork.h"
#include "../input/Controller.h"
#include <functional>


enum class UpMode
{
	SetNetWork,				// ホストかゲストの選択
	SetHostIP,				// ゲストのIP入力
	StartInit,				// 初期化
	Play					// ゲーム中
};

class LoginScene :
	public BaseScene
{
public:
	LoginScene();
	~LoginScene();
	void init(void) override;
	uniqueScene Update(uniqueScene own) override;
	void Draw(void) override;
private:
	void SetNetWork(void);
	void SetHostIP(void);
	void StartInit(void);
	void Play(void);
	std::unique_ptr<Controller> controller_;			// コントローラー情報を格納するユニークポインタ

	int Image;
	
	int posx;
	int posy;
	int screen_size_x;
	int screen_size_y;
	std::pair<int, int> data;
	UpMode upMode;
	std::map<UpMode, std::function<void(void)>> Act_;

};

