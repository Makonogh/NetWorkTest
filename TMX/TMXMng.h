#pragma once
#include "../Parse/rapidxml.hpp"
#include "../Parse/rapidxml_utils.hpp"
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#define lpTMXMng TMXMng::GetInstance()

enum class LAYER
{
	BG,						// 背景
	ITEM,					// アイテム
	OBJ,					// オブジェクト（壊せる壁とか）
	CHAR,					// キャラの座標
	MAX,					// ボムに関してはデータとしてはTMXに持たせるけど読み込みしないためここでMAX
	BOMB					// 爆弾の設置された情報を扱うレイヤー。TMXでは読みこまないゲームシーンで追加や削除行う。
};

class TMXMng
{
public:
	static TMXMng& GetInstance()
	{
		static TMXMng s_instance;
		return s_instance;
	}
	std::map < LAYER, std::vector<int>> GetMapData();
	bool LoadTMX();
	bool LoadTSX(void);
	bool SendMapData(void);
	std::pair<int, int> GetMapSize(void);
private:
	TMXMng();
	~TMXMng();
	void ShowData(rapidxml::xml_node<>* node, int indent = 0);
	// 読み込んだtmxをとりあえずノード　データ　アトリビュート全部コンソールに表示する
	bool LoadMapData(rapidxml::xml_node<>* node);	// マップデータをLayerMap_に格納する
	bool LoadCSV();		// CSVを抽出
	
	int width;
	int length;
	std::map < LAYER, std::vector<int>> LayerMap_;
	std::vector<unsigned int> CSV_;							// TMXのCSV部分の数字だけを格納
};

