#pragma once
#include "BaseScene.h"
#include "../Obj/Obj.h"
#include "../TMX/TMXMng.h"
#include <vector>
#include <map>
#include <functional>
#include <list>

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
	void SetBomb();													// ���e�̐ݒu�iChar�N���X���Ăԁj
	void SetGene(Vector2 tipos);									
	std::list<std::shared_ptr <Obj>> GetObj();						// Obj�N���X��������
	uniqueScene Update(uniqueScene own) override;					// �A�b�v�f�[�g
	void Draw() override;											// �摜�`��(Obj����̌p��)
	std::vector<unsigned char>& GetMapData_(LAYER layer);
private:
	int TileSet_[12];												// �摜�o���h��(map.png)
	int FireSet_[12];												// �摜�o���h��(fire.png)
	std::map < LAYER, std::vector<unsigned char>> mapData_;					// �}�b�v�f�[�^(TMXMng����󂯎���Ċi�[����)
	std::map<UpDate, std::function<bool(void)>> Update_;			// �֐��I�u�W�F�N�g
	std::list<std::shared_ptr <Obj>> ObjList_;						// �I�u�W�F�N�g���Ǘ�����x�N�^�[
	std::list<std::shared_ptr <Obj>> CharList_;						// �L�������Ǘ�����x�N�^�[
};
