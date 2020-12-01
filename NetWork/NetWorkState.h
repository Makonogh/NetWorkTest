#pragma once
#include <DxLib.h>
#include <list>

enum class NetWorkMode
{
	NON,			// 未設定
	OFFLINE,		
	HOST,
	GUEST,
	MAX
};

enum class ActiveState
{
	Non,			// 未設定
	Wait,			// 接続待機状態(ホスト)
	Init,			// 初期化中(ゲーム開始準備中、両方で使う)
	Stanby,			// 初期化情報送信済みの開始まち(ホスト用)
	Play,			// ゲームプレイ中
	OFFLINE
};

using ListInt = std::list<std::pair<int,unsigned int>>;				// ネットワークハンドル,キャラ

class NetWorkState
{
public:
	NetWorkState();
	virtual ~NetWorkState();
	virtual NetWorkMode GetMode(void) { return NetWorkMode::OFFLINE; };
	ActiveState GetActive_(void);
	int GetnetHandle(void);
	virtual ActiveState ConnectHost(IPDATA hostIP);
	virtual bool Update(void);
	bool SetActive(ActiveState active);		// 状態変更する
	bool CloseNetWork(void);
private:
	virtual bool CheckNetWork(void) { return false; };	
protected:
 	const int portNum_ = 8086;				// ポートナンバー
	ActiveState active_;					// アクティブ
	int netHandle_ = 0;						// ネットハンドル格納
	ListInt playerlist_;
};
