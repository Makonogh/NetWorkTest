#include "NetWork.h"
#include "GuestState.h"
#include "HostState.h"
#include "../_debug/_DebugConOut.h"
#include "../TMX/TMXMng.h"
#include "../Scene/SceneMng.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>

bool NetWork::SetNetWorkMode(NetWorkMode mode)
{
	MesHeader data = {};
	startFlag_ = false;
	auto b = sizeof(data);
	if (mode == NetWorkMode::GUEST)
	{
		state_ = std::make_unique<GuestState>();
		Init();
		return true;
	}
	else if (mode == NetWorkMode::HOST)
	{
		state_ = std::make_unique<HostState>();
		Init();
		return true;
	}
	else // ｵﾌﾗｲﾝ
	{
		if (mode != NetWorkMode::OFFLINE)
		{
			//異常検出（例外）
			TRACE("ネットワークのモード指定エラー");
			return false;
		}
		state_ = std::make_unique<NetWorkState>();
		return true;
	}
	return false;
}

NetWorkMode NetWork::GetNetWorkMode()
{
	return state_->GetMode();
}

ActiveState NetWork::GetActive(void)
{
	return state_->GetActive_();
}

ActiveState NetWork::ConnectHost(IPDATA hostIP)
{
	return  state_->ConnectHost(hostIP);
}

void NetWork::SendMes(MesType mesType, MesPacket data, int ID)
{
	Header header = {};
	for (auto& d : state_->GetPlayerList())
	{
		if (ID == d.CharID)
		{
			short id = 0;							// 分割時のナンバリングカウント
			header.mesHeader.type = mesType;
			data.emplace(data.begin(), unionData{ header.intHeader[1] });
			data.emplace(data.begin(), unionData{ header.intHeader[0] });
			do {
				if (intSendCount_ >= data.size() * 4)
				{
					header.mesHeader.next = 0;
					header.mesHeader.length_ = data.size() - 2;
					header.mesHeader.sendID = id;
					data[0] = { header.intHeader[0] };
					data[1] = { header.intHeader[1] };
					NetWorkSend(d.NWHandle, data.data(), data.size() * sizeof(unionData));
					data.erase(data.begin() + 2, data.end());
				}
				else
				{
					header.mesHeader.next = 1;
					header.mesHeader.length_ = intSendCount_ / 4 - 2;
					header.mesHeader.sendID = id;
					data[0] = { header.intHeader[0] };
					data[1] = { header.intHeader[1] };
					NetWorkSend(d.NWHandle, data.data(), intSendCount_);
					data.erase(data.begin() + 2, data.begin() + 2 + (intSendCount_ / 4));
				}
			} while (data.size() > 2);
		}
	}
}

void NetWork::SendMes(MesType type, int ID)
{
	MesPacket expData;
	SendMes(type, expData, ID);
}

void NetWork::SendAllMes(MesType mesType, MesPacket data)
{
	Header header = {};
	for (auto& d : state_->GetPlayerList())
	{
		short id = 0;							// 分割時のナンバリングカウント
		header.mesHeader.type = mesType;
		data.emplace(data.begin(), unionData{ header.intHeader[1] });
		data.emplace(data.begin(), unionData{ header.intHeader[0] });
		do {
			if (intSendCount_ >= data.size() * 4)
			{
				header.mesHeader.next = 0;
				header.mesHeader.length_ = data.size() - 2;
				header.mesHeader.sendID = id;
				data[0] = { header.intHeader[0] };
				data[1] = { header.intHeader[1] };
				NetWorkSend(d.NWHandle, data.data(), data.size() * sizeof(unionData));
				data.erase(data.begin() + 2, data.end());
			}
			else
			{
				header.mesHeader.next = 1;
				header.mesHeader.length_ = intSendCount_ / 4 - 2;
				header.mesHeader.sendID = id;
				data[0] = { header.intHeader[0] };
				data[1] = { header.intHeader[1] };
				NetWorkSend(d.NWHandle, data.data(), intSendCount_);
				data.erase(data.begin() + 2, data.begin() + 2 + (intSendCount_ / 4));
			}
		} while (data.size() > 2);
	}
}

void NetWork::SendAllMes(MesType type)
{
	MesPacket expData;
	SendAllMes(type, expData);
}


std::tuple<unsigned int, unsigned int, unsigned int> NetWork::GetTMXState()
{
	return { width_,length_,layer_ };
}

std::pair<int, int> NetWork::GetPlayerID()
{
	return { MyID_,MaxPlayer_ };
}

std::array<IPDATA, 2> NetWork::GetIp(void)
{
	GetMyIPAddress(&arrayIP_[0], 2);
	return arrayIP_;
}

void NetWork::Init()
{
	revFunc_[MesType::COUNT_DOWN_ROOM] = [&]() {};

	revFunc_[MesType::ID] = [&]() {
		MyID_ = revData_[MesType::ID][0].iData;
		MaxPlayer_ = revData_[MesType::ID][1].iData;
	};

	revFunc_[MesType::TMX_SIZE] = [&]() {
		width_ = revData_[MesType::TMX_SIZE][0].cData[0];
		length_ = revData_[MesType::TMX_SIZE][0].cData[1];
		layer_ = revData_[MesType::TMX_SIZE][0].cData[2];
		revData_.erase(MesType::TMX_SIZE);
	};

	revFunc_[MesType::TMX_DATA] = [&]() {
		lpTMXMng.LoadRevTMX(revData_[MesType::TMX_DATA]);
		revData_.erase(MesType::TMX_DATA);
	};

	revFunc_[MesType::STANBY_HOST] = [&]() {
		revData_.erase(MesType::STANBY_HOST);
			startFlag_ = true; 
		};

	revFunc_[MesType::STANBY_GUEST] = [&]() {
		revData_.erase(MesType::STANBY_GUEST);
		startFlag_ = true; };

	revFunc_[MesType::COUNT_DOWN_GAME] = [&]() {
		revData_.erase(MesType::COUNT_DOWN_GAME);
		startFlag_ = true; };

	revFunc_[MesType::POS] = [&]() {
		revPos_[revData_[MesType::POS][0].iData][0] = revData_[MesType::POS][1].iData;
		revPos_[revData_[MesType::POS][0].iData][1] = revData_[MesType::POS][2].iData;
		revPos_[revData_[MesType::POS][0].iData][2] = revData_[MesType::POS][3].iData;
	};

	revFunc_[MesType::SET_BOMB] = [&]() {
		revBomb_[revData_[MesType::SET_BOMB][0].iData][0] = revData_[MesType::SET_BOMB][1].iData;			// bombのID
		revBomb_[revData_[MesType::SET_BOMB][0].iData][1] = revData_[MesType::SET_BOMB][2].iData;			// x座標
		revBomb_[revData_[MesType::SET_BOMB][0].iData][2] = revData_[MesType::SET_BOMB][3].iData;			// y座標
		revBomb_[revData_[MesType::SET_BOMB][0].iData][3] = revData_[MesType::SET_BOMB][4].iData;			// length
		revBomb_[revData_[MesType::SET_BOMB][0].iData][4] = revData_[MesType::SET_BOMB][5].iData;			// 時間
		revBomb_[revData_[MesType::SET_BOMB][0].iData][5] = revData_[MesType::SET_BOMB][6].iData;			// 時間
		
	};

	revFunc_[MesType::RESULT] = [&]() {
		for (auto data : revData_[MesType::RESULT])
		{
			if (data.iData >= 0)
			{
				TRACE("%d\n", data.iData / 5 + 1);
			}
		}
	};

	revFunc_[MesType::DETH] = [&]() {
		revDeth_[revData_[MesType::DETH][0].iData] = true;
		return;
	};

	std::thread th(&NetWork::RevUpdate, this);
	th.detach();
}

bool NetWork::Update()
{
	return state_->Update();
}

bool NetWork::CloseNetWork(void)
{
	return false;
}

void NetWork::SendStanby()
{
	/*std::ifstream ifp("image/mapBomb.tmx");*/

	/*Header header;
	MesPacket data;*/
	//ifp.seekg(0, std::ios_base::end);
	//unsigned int size = static_cast<int>(ifp.tellg()) / 4;
	/*ifp.seekg(0, std::ios_base::beg);*/
	/*unsigned int size = lpTMXMng.GetCSV().size();
	header = { MesType::TMX_SIZE,0,0,1 };
	data.insert(data.begin(), {size});
	SortMes(header,data);
	*/
	start = std::chrono::system_clock::now();

	lpTMXMng.SendMapData();
	/*auto id = 0;*/

	//for (auto s = size;s -= 250;s <= 0)
	//{
	//	header = { MesType::TMX_DATA,0,0,size };
	//	data.clear();
	//	data.resize(250);
	//	for (auto i = 0;i++; i >= 250)
	//	{
	//		data[i] = ifp);
	//	}
	//	id++;
	//}

	//std::string str;
	//std::stringstream stringstr;
	//unsigned short id = 0;
	//udata.lData = NULL;
	//int wcount = 0;
	//while (!ifp.eof())
	//{
	//	do
	//	{
	//		std::getline(ifp, str);
	//		if (ifp.eof())
	//		{
	//			break;
	//		}
	//	} while (str.find("data encoding") == std::string::npos);
	//	if (!ifp.eof())
	//	{
	//		std::getline(ifp,str);
	//		stringstr << str;
	//		while (stringstr.eof())
	//		{
	//			if (str.find("/data") != std::string::npos)
	//			{
	//				break;
	//			}
	//		}
	//		while (std::getline(ifp, str, ','))
	//		{
	//			if (str.find("</data>") != std::string::npos)
	//			{
	//				const char* str1 = &str.erase(0);
	//				const char* str2 = &str[str.size() - 1];
	//				if (((wcount % 16) % 2) == 0)
	//				{
	//					udata.cData[(wcount % 16) / 2] |= std::atoi(str1);
	//					wcount++;
	//				}
	//				else
	//				{
	//					udata.cData[(wcount % 16) / 2] |= std::atoi(str1) << 4;
	//					wcount++;
	//				}
	//				if (wcount % 16 == 0)
	//				{
	//					data = { MesType::TMX_DATA,id,0,udata.iData[0],udata.iData[1] };
	//					id++;
	//					NetWorkSend(hand, &data, sizeof(data));
	//					udata.lData = NULL;
	//				}
	//				if (((wcount % 16) % 2) == 0)
	//				{
	//					udata.cData[(wcount % 16) / 2] |= std::atoi(str2);
	//					wcount++;
	//				}
	//				else
	//				{
	//					udata.cData[(wcount % 16) / 2] |= std::atoi(str2) << 4;
	//					wcount++;
	//				}
	//			}
	//			else if (str.find("\n") != std::string::npos)
	//			{
	//				str.erase(0, 1);
	//			}
	//			else
	//			{
	//				TRACE("%d\n", std::atoi(str.c_str()));
	//				if (((wcount % 16) % 2) == 0)
	//				{
	//					udata.cData[(wcount % 16) / 2] |= std::atoi(str.c_str());
	//					wcount++;
	//				}
	//				else
	//				{
	//					udata.cData[(wcount % 16) / 2] |= std::atoi(str.c_str()) << 4;
	//					wcount++;
	//				}
	//				if (wcount % 16 == 0)
	//				{
	//					data = { MesType::TMX_DATA,id,0,udata.iData[0],udata.iData[1] };
	//					id++;
	//					NetWorkSend(hand, &data, sizeof(data));
	//					udata.lData = NULL;
	//				}
	//			}
	//		}
	//	}
	//}
	//if (wcount % 16 != 0)
	//{
	//	data = { MesType::TMX_DATA,id,0,udata.iData[0],udata.iData[1] };
	//	NetWorkSend(hand, &data, sizeof(data));
	//	id++;
	//}

	end = std::chrono::system_clock::now();  // 計測終了時間
	auto time = end - start;
	auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
	std::cout << msec << " msec" << std::endl;

	state_->SetActive(ActiveState::Stanby);
}

void NetWork::RevUpdate(void)
{
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		Header header;
		std::lock_guard<std::mutex> lock(mtx);
		for (auto& data : state_->GetPlayerList())
		{
			if (sizeof(header) <= GetNetWorkDataLength(data.NWHandle))
			{
				int writePos = 0;				// データ格納のvectorの書き込み位置
				NetWorkRecv(data.NWHandle, &header, sizeof(header));

				if (header.mesHeader.length_ > 0)
				{
					revData_[header.mesHeader.type].resize(header.mesHeader.length_);
					if (sizeof(unionData) * header.mesHeader.length_ <= static_cast<unsigned int>(GetNetWorkDataLength(data.NWHandle)))
					{
						NetWorkRecv(data.NWHandle, &revData_[header.mesHeader.type][writePos], sizeof(unionData) * header.mesHeader.length_);
					}
					writePos = header.mesHeader.length_;
					while (header.mesHeader.next)
					{
						if (sizeof(header) <= GetNetWorkDataLength(data.NWHandle))
						{
							NetWorkRecv(data.NWHandle, &header, sizeof(header));
							revData_[header.mesHeader.type].resize(writePos + header.mesHeader.length_);
							if (sizeof(unionData) * header.mesHeader.length_ <= static_cast<unsigned int>(GetNetWorkDataLength(data.NWHandle)))
							{
								NetWorkRecv(data.NWHandle, &revData_[header.mesHeader.type][writePos], sizeof(unionData) * header.mesHeader.length_);
							}
						}
						writePos += header.mesHeader.length_;
					}
				}
				revFunc_[header.mesHeader.type]();
			}
		}
	}
}

bool NetWork::GetStartFlag(void)
{
	return startFlag_;
}

bool NetWork::GetDethData(int id)
{
	return revDeth_[id];
}

std::vector<unionData> NetWork::GetRevData(MesType mesType)
{
	return revData_[mesType];
}

std::array<int, 3> NetWork::GetPosData(int id)
{
	if (revPos_.find(id) == revPos_.end())
	{
		return std::array{ -1,-1,-1 };
	}
	else
	{
		return revPos_[id];
	}
}

std::array<int, 6> NetWork::GetBombData(int id)
{
	if (revBomb_.find(id) == revBomb_.end())
	{
		return std::array{ -1,-1,-1,-1,-1,-1 };
	}
	else
	{
		return revBomb_[id];
	}
}


NetWork::NetWork()
{
	arrayIP_ = { 0,0 };
	MyID_ = 0;
	MaxPlayer_ = 0;
	width_ = 0;
	length_ = 0;
	layer_ = 0;
	startFlag_ = false;
	intSendCount_ = 1000;
}

NetWork::~NetWork()
{
}
