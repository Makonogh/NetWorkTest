#include "NetWork.h"
#include "GuestState.h"
#include "HostState.h"
#include "../_debug/_DebugConOut.h"
#include "../TMX/TMXMng.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>

bool NetWork::SetNetWorkMode(NetWorkMode mode)
{
	MesHeader data;
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

void NetWork::SendMes(MesType mesType, MesPacket data,int ID)
{
	Header header;
	for (auto &d : state_->GetPlayerList())
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
					header.mesHeader.length = data.size() - 2;
					header.mesHeader.sendID = id;
					data[0] = { header.intHeader[0] };
					data[1] = { header.intHeader[1] };
					NetWorkSend(d.NWHandle, data.data(), data.size() * sizeof(unionData));
					data.erase(data.begin() + 2, data.end());
				}
				else
				{
					header.mesHeader.next = 1;
					header.mesHeader.length = intSendCount_ / 4 - 2;
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

void NetWork::SendMes(MesType type,int ID)
{
	MesPacket expData;
	SendMes(type, expData,ID);
}

void NetWork::SendAllMes(MesType mesType, MesPacket data)
{
	Header header;
	for (auto &d : state_->GetPlayerList())
	{
		short id = 0;							// 分割時のナンバリングカウント
		header.mesHeader.type = mesType;
		data.emplace(data.begin(), unionData{ header.intHeader[1] });
		data.emplace(data.begin(), unionData{ header.intHeader[0] });
		do {
			if (intSendCount_ >= data.size() * 4)
			{
				header.mesHeader.next = 0;
				header.mesHeader.length = data.size() - 2;
				header.mesHeader.sendID = id;
				data[0] = { header.intHeader[0] };
				data[1] = { header.intHeader[1] };
				NetWorkSend(d.NWHandle, data.data(), data.size() * sizeof(unionData));
				data.erase(data.begin() + 2, data.end());
			}
			else
			{
				header.mesHeader.next = 1;
				header.mesHeader.length = intSendCount_ / 4 - 2;
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
	return {width,length,layer};
}

std::array<IPDATA, 2> NetWork::GetIp(void)
{
	GetMyIPAddress(&arrayIP_[0],2);
	return arrayIP_;
}

void NetWork::Init()
{
	revFunc_[MesType::COUNT_DOWN_ROOM] = [&]() { return; };
	
	revFunc_[MesType::ID] = [&]() {  return; };

	revFunc_[MesType::TMX_SIZE] = [&]() { 
		width  = revData_[MesType::TMX_SIZE][0].cData[0];
		length = revData_[MesType::TMX_SIZE][0].cData[1];
		layer = revData_[MesType::TMX_SIZE][0].cData[2];
		revData_.erase(MesType::TMX_SIZE);
	};

	revFunc_[MesType::TMX_DATA] = [&]() { 
		lpTMXMng.LoadRevTMX(revData_[MesType::TMX_DATA]);
		revData_.erase(MesType::TMX_DATA);
	};

	revFunc_[MesType::STANBY_HOST] = [&]() {startFlag_ = true; };

	revFunc_[MesType::STANBY_GUEST] = [&]() {startFlag_ = true; };

	revFunc_[MesType::COUNT_DOWN_GAME] = [&]() {};

	revFunc_[MesType::POS] = [&]() {};
	
	revFunc_[MesType::SET_BOMB] = [&]() {};

	revFunc_[MesType::DETH] = [&]() {};

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

void NetWork::SendStart()
{
	//auto hand = state_->GetnetHandle();
	//MesHeader data;
	//data.type = MesType::GAMESTART;
	//NetWorkSend(hand, &data, sizeof(data));
	//TRACE("スタート信号送信");
	//state_->SetActive(ActiveState::Play);
}

bool NetWork::GetRevStanby(void)
{
	


 	
	//if (b > 4)
	//{
	//	NetWorkRecv(hand, &header, sizeof(header));
	//	TRACE("受信");
	//	NetWorkRecv(hand, &data, header.mesHeader.length * sizeof(int));
	//	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();

	//	TRACE("受信");
	//}
	//while (GetNetWorkDataLength(hand) >= sizeof(data))
	//{
	//	
	//	if (data.type == MesType::TMX_SIZE)
	//	{
	//		start = std::chrono::system_clock::now();
	//		RevTMX_.resize(data.data[0]);
	//		TRACE("受け取るTMXサイズは%dです。\n", RevTMX_.size());
	//	}
	//	if (data.type == MesType::TMX_DATA)
	//	{
	//		RevTMX_[data.data[0]] = data.data[1];
	//		TRACE("%c",RevTMX_[data.data[0]]);
	//	}
	//	if (data.type == MesType::STANBY)
	//	{
	//		std::ofstream ofs("mapdata.tmx");
	//		if (!ofs)
	//		{
	//			std::cerr << "ファイルオープンに失敗" << std::endl;
	//			std::exit(1);
	//		}
	//		for (auto x : RevTMX_)
	//		{
	//			if (x != NULL)
	//			{
	//				ofs << x;
	//			}
	//		}
	//		end = std::chrono::system_clock::now();  // 計測終了時間
	//		auto time = end - start; 
	//		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
	//		TRACE("初期化信号受信\n");
	//		// 処理に要した時間をミリ秒に変換
	//		
	//		std::cout << msec << " msec" << std::endl;
	//		return true;
	//	}
	//}
	return true;
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

				revData_[header.mesHeader.type].resize(header.mesHeader.length);
				if (header.mesHeader.length > 0)
				{

					if (sizeof(unionData) * header.mesHeader.length <= GetNetWorkDataLength(data.NWHandle))
					{
						NetWorkRecv(data.NWHandle, &revData_[header.mesHeader.type][writePos], sizeof(unionData) * header.mesHeader.length);
					}
					writePos = header.mesHeader.length;
					while (header.mesHeader.next)
					{
						if (sizeof(header) <= GetNetWorkDataLength(data.NWHandle))
						{
							NetWorkRecv(data.NWHandle, &header, sizeof(header));
							revData_[header.mesHeader.type].resize(writePos + header.mesHeader.length);
							if (sizeof(unionData) * header.mesHeader.length <= GetNetWorkDataLength(data.NWHandle))
							{
								NetWorkRecv(data.NWHandle, &revData_[header.mesHeader.type][writePos], sizeof(unionData) * header.mesHeader.length);
							}
						}
						writePos += header.mesHeader.length;
					}
				}
				revFunc_[header.mesHeader.type]();
				TRACE("受信");
			}
		}
	}
}

bool NetWork::GetStartFlag(void)
{
	return startFlag_;
}

void NetWork::GetRevStart(void)
{

}

NetWork::NetWork()
{
	intSendCount_ = 1000;
}

NetWork::~NetWork()
{
}
