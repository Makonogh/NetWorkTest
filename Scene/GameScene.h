#pragma once
#include "BaseScene.h"
#include "../Obj/Obj.h"
#include "../TMX/TMXMng.h"
#include <vector>
#include <map>
#include <functional>

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
	uniqueScene Update(uniqueScene own) override;					// アップデート
	void Draw() override;											// 画像描画(Objからの継承)
private:
	int TileSet_[12];												// 画像バンドル(mapBomb)
	std::map < LAYER, std::vector<int>> mapData_;					// マップデータ(TMXMngから受け取って格納する)
	std::map<UpDate, std::function<bool(void)>> Update_;			// 関数オブジェクト
	std::vector<std::shared_ptr <Obj>> ObjList_;					// オブジェクトを管理するベクター
	std::vector<std::shared_ptr <Obj>> CharList_;					// キャラを管理するベクター
};
