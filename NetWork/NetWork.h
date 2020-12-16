#pragma once
#include "NetWorkState.h"
#include <DxLib.h>
#include <memory>
#include <vector>
#include <array>
#include <chrono>
#include <functional>
#include <map>
#include <mutex>
#include <tuple>

#define lpNetWork NetWork::GetInstance()

//using uniNetMode = std::unique_ptr<NetWorkState>;
enum class  MesType : unsigned char
{
	NON = 100,			// -------------------------------------l�f�[�^���̓��e
	COUNT_DOWN_ROOM,	// �ڑ���t�J�E���g�_�E��				l �ڑ��J�n���ꂽ���� (�N���m)
	ID,					// ������ID�ƃv���C���[����				l ������ID�ƑS�v���C���[����
	STANBY_HOST,		// ��������(�z�X�g�p)					l �Ȃ�
	STANBY_GUEST,		// ��������(�Q�X�g�p)					l �Ȃ�
	COUNT_DOWN_GAME,	// �S���̏�����������̃Q�[���J�n����	l �Q�[���̊J�n����(�N���m)
	TMX_SIZE,			// CSV�̃T�C�Y							l int{���̃}�X,�c�̃}�X,���C���[�̐�}
	TMX_DATA,			// TMX�f�[�^��CSV						l TMX�̃f�[�^( int = char{��4�r�b�g,��4�r�b�g} * 4)
	POS,				// �Q�[�����̃f�[�^						l ID,X,Y,����
	SET_BOMB,			// �{���̐ݒu							l �I�[�i�[ID.���g��ID,X,Y,length,����{int * 2}
	DETH,				// ���S �L������ID�t�^					l �L������ID
	RESULT, 			// ���U���g								l �D������unsigned int (charID)
	LOST,				// �ؒf���ɐ���							l �Ȃ�
	MAX
	/// �p�P�b�g�̎�ރf�[�^
};

struct MesHeader			// �v8�o�C�g
{
	MesType type;			// 1�o�C�g ���b�Z�[�W�̎��
	unsigned char next;		// 1�o�C�g �����̏ꍇ�@��������1 �Ȃ�0
	unsigned short sendID;  // 2�o�C�g �������̃i���o�����O
	unsigned int length_;    // 4�o�C�g �f�[�^���̒���(int��)
};

union Header
{
	MesHeader mesHeader;			// 8�o�C�g
	unsigned int intHeader[2];		// 4*2�o�C�g
};

union unionData
{
	unsigned int uData;		// 4�o�C�g
	char cData[4];          // 1*4�o�C�g
	unsigned char ucData[4];// 1*4�o�C�g
	int iData;			    // 4�o�C�g
};

using MesPacket = std::vector<unionData>; 

class NetWork
{
public:
	static NetWork& GetInstance(void)
	{
		static NetWork s_Instance;
		return s_Instance;
	}
	bool SetNetWorkMode(NetWorkMode mode);
	ActiveState ConnectHost(IPDATA hostIP);
	void SendMes(MesType type,MesPacket data,int ID);	// �f�[�^�𑗂�(�^�C�v�ƃf�[�^��������)
	void SendMes(MesType type,int ID);					// �f�[�^�𑗂�(�^�C�v����)
	void SendAllMes(MesType type,MesPacket data);		// �f�[�^�𑗂�(���ׂĂ�)
	void SendAllMes(MesType type);						// �f�[�^�𑗂�(���ׂĂɃf�[�^���Ȃ�)
	bool Update();
	void RevUpdate(void);				// �f�[�^���󂯎��revData�ɓK�؂ȃL�[�Ŋi�[����֐�
	bool CloseNetWork(void);			
	void SendStanby();					// �z�X�g���Q�X�g�ɏ������M���𑗂�֐�
	
	bool GetStartFlag(void);			// �X�^�[�g�t���O�̃Q�b�g�֐�
	NetWorkMode GetNetWorkMode();
	ActiveState GetActive(void);
	std::vector<unionData> GetRevData(MesType mesType);						// �����̃^�C�v�̃f�[�^�̃Q�b�g�֐�
	std::tuple<unsigned int, unsigned int, unsigned int> GetTMXState();		// width,length,layer
	std::pair<int, int> GetPlayerID();										// MyID,MaxPlayer
	std::array<IPDATA, 2> GetIp(void);	
private:
	void Init();
	unsigned int intSendCount_;			// ���M�o�C�g��(ini�t�@�C����setting.txt����̓ǂݍ���)
	
	std::vector<int> RevTMX_;			
	std::array<IPDATA, 2> arrayIP_;
 	std::unique_ptr<NetWorkState> state_;
	std::vector<int> MapData_;
	std::map < MesType, std::function<void(void)>> revFunc_;				// �֐��|�C���^
	std::map < MesType, std::vector<unionData> > revData_;					// �󂯎�����f�[�^��ۑ�
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	std::pair<MesType, MesPacket> MesData_;								
	std::mutex mtx;

	unsigned int width_;
	unsigned int length_;
	unsigned int layer_;
	unsigned int MyID_;
	unsigned int MaxPlayer_;

	bool startFlag_;
	
	NetWork();
	~NetWork();
};

