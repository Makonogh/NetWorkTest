#pragma once
#include "NetWorkState.h"
#include <DxLib.h>
#include <memory>
#include <vector>
#include <array>
#include <chrono>

#define lpNetWork NetWork::GetInstance()

//using uniNetMode = std::unique_ptr<NetWorkState>;
enum class  MesType : unsigned char
{
	STANBY,
	GAMESTART,
	TMX_SIZE,
	TMX_DATA,
	POS						// �Q�[�����̃f�[�^
};

struct MesHeader
{
	MesType type;			// 1�o�C�g
	unsigned short id;	    // 2�o�C�g
	unsigned char cdata;	// 1�o�C�g
	unsigned int length;   
	//int data[2];			// 8�o�C�g
};

union unionData
{
	char cData[8];          // 1�o�C�g�~8
	int iData[2];			// 4�o�C�g�~2
	long long lData;		// 8�o�C�g
};

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
	int GetHandle(void);
	std::array<IPDATA, 2> GetIp(void);
	bool Update();
	bool CloseNetWork(void);
	bool SendMes(MesHeader& data);				
	void SendStanby();					// �z�X�g���Q�X�g�ɏ������M���𑗂�֐�
	void GetRevStart(void);				// �z�X�g���Q�X�g�̃X�^�[�g���󂯎��֐�
	void SendStart();					// �Q�X�g���z�X�g�ɏ����������������Ƃ𑗂�֐�
	bool GetRevStanby(void);			// �Q�X�g���z�X�g�̏������M�����󂯎���
private:
	/*uniNetMode netMode_;*/
	std::vector<int> RevTMX_;			
	std::array<IPDATA, 2> arrayIP_;
 	std::unique_ptr<NetWorkState> state_;
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	
	
	NetWork();
	~NetWork();
};

