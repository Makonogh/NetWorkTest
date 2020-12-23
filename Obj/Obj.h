#pragma once
#include "../common/Vector2.h"
#include "../Scene/BaseScene.h"
#include <vector>
#include <memory>
#include <list>

enum class OBJ_TYPE
{
	CHAR,
	WALL,
	ITEM,
	BOMB,
	GENE,
	MAX
};

class Obj
{
public:
	Obj();
	Vector2 GetPos();						// ���W�̃Q�b�g�֐�
	Vector2 GetTilePos();					// �^�C�����W�̃Q�b�g�֐�
	OBJ_TYPE GetType();						// �^�C�v�̃Q�b�g�֐�
	virtual void Draw();					// �`��
	virtual void Draw(int* TileImg);		// �`��
	virtual void Update();					// Update
	virtual void UpdateOpe();				// �v���C���[�N���X�̑��삷��֐�(char���g�p
	virtual void UpdateAuto();				// �I�[�g�p�C���b�g�ő��삷��֐�(char���g�p
	virtual void UpdateRev();				// �l�b�g�̊l�����ő��삷��֐�(char���g�p
	virtual bool GetFlag();
	virtual ~Obj() = 0;
protected:
	OBJ_TYPE type_;					// �����̃I�u�W�F�N�g�̃^�C�v	
	Vector2 pos_;					// ���W
	Vector2 size_;					// �T�C�Y
	Vector2 tilePos_;				// �}�X�ڍ��W
};

