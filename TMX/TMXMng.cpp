#include "TMXMng.h"
#include "../NetWork/NetWork.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

TMXMng::TMXMng()
{
	width = 21;
	length = 17;
	LayerMap_[LAYER::BG].resize(21 * 17);
	LayerMap_[LAYER::ITEM].resize(21 * 17);
	LayerMap_[LAYER::OBJ].resize(21 * 17);
	LayerMap_[LAYER::CHAR].resize(21 * 17);	
	LayerMap_[LAYER::BOMB].resize(21 * 17);
}

TMXMng::~TMXMng()
{
}

std::map<LAYER, std::vector<int>> TMXMng::GetMapData()
{
	return LayerMap_;
}

bool TMXMng::LoadTMX()
{
	rapidxml::xml_document<> doc;		// Xmlを読み込むDom
	rapidxml::file<> file("image/mapBomb.tmx");
	doc.parse<0>(file.data());
	rapidxml::xml_node<>* node = doc.first_node("map");
	LoadMapData(node);
	/*ShowData(doc.first_node());*/
	LoadCSV();
	return false;
}

bool TMXMng::LoadTSX(void)
{
	return false;
}

bool TMXMng::SendMapData(void)
{
	MesPacket expData;
	unionData data;
	data.cData[0] = 21;
	data.cData[1] = 17;
	data.cData[2] = 4;
	data.cData[3] = 0;

	expData.emplace_back(data);

	lpNetWork.SendMes(MesType::TMX_SIZE,expData);
	
	expData.clear();
	for (auto x:CSV_)
	{
		expData.emplace_back();
	}

	lpNetWork.SendMes(MesType::TMX_DATA,expData);

	lpNetWork.SendMes(MesType::STANBY);
	return false;
}

std::pair<int, int> TMXMng::GetMapSize(void)
{
	std::pair<int, int> redata;
	redata.first = width;
	redata.second = length;
	return redata;
}

void TMXMng::ShowData(rapidxml::xml_node<>* node, int indent)
{
	//ノードがなければなにもしない
	if (node == nullptr) return;
	//名前があるか
	if (node->name_size() > 0)
	{
		//インデント分タブ入れる
		for (int i = 0; i < indent; i++) std::cout << "\t";
		std::cout << "Node:" << node->name() << "\n";

		for (rapidxml::xml_attribute<>*atb = node->first_attribute();
			atb != nullptr;
			atb = atb -> next_attribute())
		{
			for (int i = 0; i < indent; i++) std::cout << "\t";
			std::cout << atb->name() ;
			std::cout << ":{" << atb->value() <<"}"<< "\n";
		}
	}
	else return;
	if (node->value_size() > 0)
	{
		//インデントとノード分タブ入れる
		std::cout << node->value() << "\n";
		return;
	}
	//子ノードへ
	ShowData(node->first_node(), indent + 1);
	//弟ノードへ
	ShowData(node->next_sibling(), indent);
}

bool TMXMng::LoadMapData(rapidxml::xml_node<>* node)
{
	
	for (rapidxml::xml_node<>* layer = node->first_node()->next_sibling("layer");
		layer != nullptr;
		layer = layer->next_sibling())
	{
		rapidxml::xml_attribute<>* atb = layer->first_attribute("id");

		LAYER layerNum = static_cast<LAYER> (atoi(atb->value()) - 1);

		std::istringstream iss(layer->first_node()->value());
		std::string str;
		std::vector<std::string> result;
		
		while (std::getline(iss, str, ','))
		{
			result.push_back(str);
		}
		for (int x = 0; x < 21 * 17; x++)
		{
			LayerMap_[layerNum][x] = std::atoi(result[x].c_str()) - 1;
		}
	}
	return false;
}

bool TMXMng::LoadCSV()
{
	int csvnum = 0;
	for (auto y = 0;y < 4;y++)
	{
		for(int x = 0; x < 21 * 17; x++)
		{
			CSV_.emplace_back(LayerMap_[static_cast<LAYER>(y)][x] );
			csvnum++;
		}
	}
	return false;
}
