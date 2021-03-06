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
	HostUpdate,				// ホストのアップデート
	GuestUpdate,			// ゲストのアップデート
	OffUpdate,				// オフラインのアップデート
};

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	void SetBomb(Vector2 pos,int length, std::chrono::system_clock::time_point t);													// 爆弾の設置（Charクラスが呼ぶ）
	void SetGene(Vector2 tipos);
	std::list<std::shared_ptr <Obj>> GetObj();						// Objクラスを見たい
	uniqueScene Update(uniqueScene own) override;					// アップデート
	void Draw() override;											// 画像描画(Objからの継承)
	std::vector<unsigned char>& GetMapData_(LAYER layer_);
	std::pair<unsigned int,unsigned int> GetID();					// 自分のIDのゲット関数
private:
	int TileSet_[12];												// 画像バンドル(map.png)
	int FireSet_[12];												// 画像バンドル(fire.png)
	std::map < LAYER, std::vector<unsigned char>> mapData_;			// マップデータ(TMXMngから受け取って格納する)
	std::map<UpDate, std::function<bool(void)>> Update_;			// 関数オブジェクト
	std::list<std::shared_ptr <Obj>> ObjList_;						// オブジェクトを管理するベクター
	std::list<std::shared_ptr <Obj>> PlayerList_;					// キャラを管理するベクター
	std::list<std::shared_ptr <Obj>> ItemList_;						// アイテムを管理するベクター

	unsigned int myID_;
	unsigned int playerMax_;
};
