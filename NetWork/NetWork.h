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
	COUNT_DOWN_ROOM,	// 接続受付カウントダウン
	ID,					// 自分のIDとプレイヤー総数
	STANBY_HOST,		// 準備完了(ホスト用)
	STANBY_GUEST,		// 準備完了(ゲスト用)
	COUNT_DOWN_GAME,	// 全員の初期化完了後のゲーム開始時間
	TMX_SIZE,			// CSVのサイズ
	TMX_DATA,			// TMXデータのCSV
	POS,				// ゲーム中のデータ
	SET_BOMB,			// ボムの設置 
	DETH,				// 死亡 キャラのID付与
	LOST,				// 切断時に生成
	MAX
	/// パケットの種類データ
};

struct MesHeader			// 計8バイト
{
	MesType type;			// 1バイト メッセージの種類
	unsigned char next;		// 1バイト 分割の場合　次がある1 ない0
	unsigned short sendID;  // 2バイト 分割時のナンバリング
	unsigned int length;    // 4バイト データ部の長さ(int長)
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
	void SendMes(MesType type,MesPacket data,int ID);	// データを送る(タイプとデータ部がある)
	void SendMes(MesType type,int ID);					// データを送る(タイプだけ)
	void SendAllMes(MesType type,MesPacket);			// データを送る(すべてに)
	void SendAllMes(MesType type);						// データを送る(すべてにデータ部なし)
	bool Update();
	bool CloseNetWork(void);			
	void SendStanby();					// ホストがゲストに初期化信号を送る関数
	void GetRevStart(void);				// ホストがゲストのスタートを受け取る関数
	void SendStart();					// ゲストがホストに初期化完了したことを送る関数
	bool GetRevStanby(void);			// ゲストがホストの初期化信号を受け取る関数
	void RevUpdate(void);				// データを受け取りrevDataに適切なキーで格納する関数
	std::array<IPDATA, 2> GetIp(void);	
private:
	void Init();
	unsigned int intSendCount_;			// 送信バイト長(iniファイルのsetting.txtからの読み込み)
	
	std::vector<int> RevTMX_;			
	std::array<IPDATA, 2> arrayIP_;
 	std::unique_ptr<NetWorkState> state_;
	std::vector<int> MapData_;
	std::map < MesType, std::function<void(void)>> revFunc_;				// 関数ポインタ
	std::map < MesType, std::vector<unionData> > revData_;					// 受け取ったデータを保存
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	std::pair<MesType, MesPacket> MesData_;								
	std::mutex mtx;
	
	NetWork();
	~NetWork();
};

