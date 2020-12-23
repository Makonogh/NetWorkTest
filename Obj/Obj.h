#pragma once
#include "../common/Vector2.h"
#include "../Scene/BaseScene.h"
#include <vector>
#include <memory>
#include <list>

enum class OBJ_TYPE
{
	CHAR,
	WALL,
	ITEM,
	BOMB,
	GENE,
	MAX
};

class Obj
{
public:
	Obj();
	Vector2 GetPos();						// 座標のゲット関数
	Vector2 GetTilePos();					// タイル座標のゲット関数
	OBJ_TYPE GetType();						// タイプのゲット関数
	virtual void Draw();					// 描画
	virtual void Draw(int* TileImg);		// 描画
	virtual void Update();					// Update
	virtual void UpdateOpe();				// プレイヤークラスの操作する関数(charが使用
	virtual void UpdateAuto();				// オートパイロットで操作する関数(charが使用
	virtual void UpdateRev();				// ネットの獲得情報で操作する関数(charが使用
	virtual bool GetFlag();
	virtual ~Obj() = 0;
protected:
	OBJ_TYPE type_;					// 自分のオブジェクトのタイプ	
	Vector2 pos_;					// 座標
	Vector2 size_;					// サイズ
	Vector2 tilePos_;				// マス目座標
};

