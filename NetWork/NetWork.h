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
	POS						// ゲーム中のデータ
};

struct MesHeader			// 計8バイト
{
	MesType type;			// 1バイト
	unsigned char cdata;	// 1バイト
	unsigned short id;	    // 2バイト
	unsigned int length;    // 4バイト			
};

union Header
{
	MesHeader mesHeader;			// 8バイト
	unsigned int intHeader[2];		// 4*2バイト
};

union unionData
{
	unsigned int uData;		// 4バイト
	char cData[4];          // 1*4バイト
	int iData;			    // 4バイト
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
	int GetHandle(void);
	std::array<IPDATA, 2> GetIp(void);
	bool Update();
	bool CloseNetWork(void);
	bool SendMes(MesHeader& data);				
	void SendStanby();					// ホストがゲストに初期化信号を送る関数
	void GetRevStart(void);				// ホストがゲストのスタートを受け取る関数
	void SendStart();					// ゲストがホストに初期化完了したことを送る関数
	bool GetRevStanby(void);			// ゲストがホストの初期化信号を受け取る関
private:
	void SendMes(MesPacket& data);
	void SortMes(Header& header,MesPacket& data);
	
	std::vector<int> RevTMX_;			
	std::array<IPDATA, 2> arrayIP_;
 	std::unique_ptr<NetWorkState> state_;
	std::vector<int> MapData_;
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	
	NetWork();
	~NetWork();
};

