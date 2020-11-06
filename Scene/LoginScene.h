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
	void init(void) override;
	uniqueScene Update(uniqueScene own) override;
	void Draw(void) override;
private:
	void SetNetWork(void);
	void SetHostIP(void);
	void StartInit(void);
	void Play(void);
	std::unique_ptr<Controller> controller_;			// �R���g���[���[�����i�[���郆�j�[�N�|�C���^

	int Image;
	
	int posx;
	int posy;
	int screen_size_x;
	int screen_size_y;
	std::pair<int, int> data;
	UpMode upMode;
	std::map<UpMode, std::function<void(void)>> Act_;

};

