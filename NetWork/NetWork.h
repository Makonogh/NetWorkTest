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

#define lpNetWork NetWork::GetInstance()

//using uniNetMode = std::unique_ptr<NetWorkState>;
enum class  MesType : unsigned char
{
	NON = 100,
	COUNT_DOWN_ROOM,	// �ڑ���t�J�E���g�_�E��
	ID,					// ������ID�ƃv���C���[����
	STANBY_HOST,		// ��������(�z�X�g�p)
	STANBY_GUEST,		// ��������(�Q�X�g�p)
	COUNT_DOWN_GAME,	// �S���̏�����������̃Q�[���J�n����
	TMX_SIZE,			// CSV�̃T�C�Y
	TMX_DATA,			// TMX�f�[�^��CSV
	POS,				// �Q�[�����̃f�[�^
	SET_BOMB,			// �{���̐ݒu 
	DETH,				// ���S �L������ID�t�^
	LOST,				// �ؒf���ɐ���
	MAX
	/// �p�P�b�g�̎�ރf�[�^
};

struct MesHeader			// �v8�o�C�g
{
	MesType type;			// 1�o�C�g ���b�Z�[�W�̎��
	unsigned char next;		// 1�o�C�g �����̏ꍇ�@��������1 �Ȃ�0
	unsigned short sendID;  // 2�o�C�g �������̃i���o�����O
	unsigned int length;    // 4�o�C�g �f�[�^���̒���(int��)
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
	NetWorkMode GetNetWorkMode();
	ActiveState GetActive(void);
	ActiveState ConnectHost(IPDATA hostIP);
	void SendMes(MesType type,MesPacket data,int ID);	// �f�[�^�𑗂�(�^�C�v�ƃf�[�^��������)
	void SendMes(MesType type,int ID);					// �f�[�^�𑗂�(�^�C�v����)
	void SendAllMes(MesType type,MesPacket);			// �f�[�^�𑗂�(���ׂĂ�)
	void SendAllMes(MesType type);						// �f�[�^�𑗂�(���ׂĂɃf�[�^���Ȃ�)
	bool Update();
	bool CloseNetWork(void);			
	void SendStanby();					// �z�X�g���Q�X�g�ɏ������M���𑗂�֐�
	void GetRevStart(void);				// �z�X�g���Q�X�g�̃X�^�[�g���󂯎��֐�
	void SendStart();					// �Q�X�g���z�X�g�ɏ����������������Ƃ𑗂�֐�
	bool GetRevStanby(void);			// �Q�X�g���z�X�g�̏������M�����󂯎��֐�
	void RevUpdate(void);				// �f�[�^���󂯎��revData�ɓK�؂ȃL�[�Ŋi�[����֐�
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
	
	NetWork();
	~NetWork();
};

