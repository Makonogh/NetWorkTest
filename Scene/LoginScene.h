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
	uniqueScene Update(uniqueScene own) override;
	void Draw(void) override;
private:
	bool SetNetWork(void);
	bool SetHostIP(void);
	bool StartInit(void);
	bool Play(void);

	std::unique_ptr<Controller> controller_;			// コントローラー情報を格納するユニークポインタ
	int Image_;
	int posx;
	int posy;
	int screen_size_x;
	int screen_size_y;
	std::pair<int, int> data;
	UpMode upMode;
	std::map<UpMode, std::function<bool(void)>> Act_;
};

