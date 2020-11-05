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

struct MesHeader
{
	MesType type;			// 1バイト
	unsigned char cdata;	// 1バイト
	unsigned short id;	    // 2バイト
	unsigned int length;    // 4バイト
	//int data[2];			// 8バイト
};


union unionData
{
	char cData[4];          // 1バイト×4
	int iData;			    // 4バイト
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
	void SendStanby();					// ホストがゲストに初期化信号を送る関数
	void GetRevStart(void);				// ホストがゲストのスタートを受け取る関数
	void SendStart();					// ゲストがホストに初期化完了したことを送る関数
	bool GetRevStanby(void);			// ゲストがホストの初期化信号を受け取る関
private:
	/*uniNetMode netMode_;*/
	std::vector<int> RevTMX_;			
	std::array<IPDATA, 2> arrayIP_;
 	std::unique_ptr<NetWorkState> state_;
	std::vector<int> MapData_;
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	
	
	NetWork();
	~NetWork();
};

