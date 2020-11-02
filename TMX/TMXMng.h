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
	BG,
	ITEM,
	OBJ,
	CHAR
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
	std::vector<int> GetCSV(void);
private:
	TMXMng();
	~TMXMng();
	void ShowData(rapidxml::xml_node<>* node, int indent = 0);
	// 読み込んだtmxをとりあえずノード　データ　アトリビュート全部コンソールに表示する
	bool LoadMapData(rapidxml::xml_node<>* node);	// マップデータをLayerMap_に格納する

	std::map < LAYER, std::vector<int>> LayerMap_;
	std::vector<int> CSV_;							// TMXのCSV部分の数字だけを格納
};

