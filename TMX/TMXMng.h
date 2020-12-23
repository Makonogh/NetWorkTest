#pragma once
#include "../Parse/rapidxml.hpp"
#include "../Parse/rapidxml_utils.hpp"
#include "../NetWork/NetWork.h"
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#define lpTMXMng TMXMng::GetInstance()

enum class LAYER
{
	BG,						// �w�i
	ITEM,					// �A�C�e��
	OBJ,					// �I�u�W�F�N�g�i�󂹂�ǂƂ��j
	CHAR,					// �L�����̍��W
	MAX,					// �{���Ɋւ��Ă̓f�[�^�Ƃ��Ă�TMX�Ɏ������邯�Ǔǂݍ��݂��Ȃ����߂�����MAX
	BOMB					// ���e�̐ݒu���ꂽ�����������C���[�BTMX�ł͓ǂ݂��܂Ȃ��Q�[���V�[���Œǉ���폜�s���B
};

class TMXMng
{
public:
	static TMXMng& GetInstance()
	{
		static TMXMng s_instance;
		return s_instance;
	}
	std::map < LAYER, std::vector<unsigned char>> GetMapData();
	bool LoadTMX();
	bool LoadTSX(void);
	bool SendMapData(void);
	bool LoadRevTMX(std::vector<unionData>& data);
	bool GetFlag();
	std::pair<int, int> GetMapSize(void);
private:
	TMXMng();
	~TMXMng();
	void ShowData(rapidxml::xml_node<>* node, int indent = 0);
	// �ǂݍ���tmx���Ƃ肠�����m�[�h�@�f�[�^�@�A�g���r���[�g�S���R���\�[���ɕ\������
	bool LoadMapData(rapidxml::xml_node<>* node);	// �}�b�v�f�[�^��LayerMap_�Ɋi�[����
	bool LoadCSV();		// CSV�𒊏o
	bool startFlag_;
	unsigned int width_;
	unsigned int length_;
	unsigned int layer_;
	std::map < LAYER, std::vector<unsigned char>> LayerMap_;
	std::vector<unsigned int> CSV_;							// TMX��CSV�����̐����������i�[


	std::mutex mtx;
};

