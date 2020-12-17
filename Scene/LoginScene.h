#pragma once
#include "BaseScene.h"
#include "../NetWork/NetWork.h"
#include "../input/Controller.h"
#include <functional>


enum class UpMode
{
	SetNetWork,				// �z�X�g���Q�X�g�̑I��
	SetHostIP,				// �Q�X�g��IP����
	StartInit,				// ������
	Play					// �Q�[����
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

	std::unique_ptr<Controller> controller_;			// �R���g���[���[�����i�[���郆�j�[�N�|�C���^
	int Image_;
	int posx;
	int posy;
	int screen_size_x;
	int screen_size_y;
	std::pair<int, int> data;
	UpMode upMode;
	std::map<UpMode, std::function<bool(void)>> Act_;
};

