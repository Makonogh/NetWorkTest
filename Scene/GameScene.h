#pragma once
#include "BaseScene.h"
#include "../Obj/Obj.h"
#include "../TMX/TMXMng.h"
#include <vector>
#include <map>
#include <functional>

enum class UpDate
{
	HostUpdate,				// �z�X�g�̃A�b�v�f�[�g
	GuestUpdate,			// �Q�X�g�̃A�b�v�f�[�g
	OffUpdate,				// �I�t���C���̃A�b�v�f�[�g
};

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	uniqueScene Update(uniqueScene own) override;					// �A�b�v�f�[�g
	void Draw() override;											// �摜�`��(Obj����̌p��)
private:
	int TileSet_[12];												// �摜�o���h��(mapBomb)
	std::map < LAYER, std::vector<int>> mapData_;					// �}�b�v�f�[�^(TMXMng����󂯎���Ċi�[����)
	std::map<UpDate, std::function<bool(void)>> Update_;			// �֐��I�u�W�F�N�g
	std::vector<std::shared_ptr <Obj>> ObjList_;					// �I�u�W�F�N�g���Ǘ�����x�N�^�[
	std::vector<std::shared_ptr <Obj>> CharList_;					// �L�������Ǘ�����x�N�^�[
};
