#include "DxLib.h"
#include "LoginScene.h"
#include "../NetWork/NetWork.h"
#include "../_debug/_DebugConOut.h"
#include "../input/GamePad.h"
#include "../TMX/TMXMng.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


LoginScene::LoginScene()
{
	screen_size_x = 0;
	screen_size_y = 0;
	posx = 0;
	posy = 0;
	Image = LoadGraph("image/bakudan.png", true);
	
	GetDrawScreenSize(&screen_size_x, &screen_size_y);
	
	Act_[UpMode::SetNetWork] = std::bind(&LoginScene::SetNetWork,this);
	Act_[UpMode::SetHostIP] = std::bind(&LoginScene::SetHostIP, this);
	Act_[UpMode::StartInit] = std::bind(&LoginScene::StartInit, this);
	Act_[UpMode::Play] = std::bind(&LoginScene::Play, this);

	upMode = UpMode::SetNetWork;
}

LoginScene::~LoginScene()
{
}

void LoginScene::init(void)
{
	
}

uniqueScene LoginScene::Update(uniqueScene own)
{
	Act_[upMode]();
	lpNetWork.Update();
	Draw();
	return own;
}

void LoginScene::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawGraph(0,0,Image,true);
	ScreenFlip();
}

void LoginScene::SetNetWork(void)
{
	auto ipData = lpNetWork.GetIp();
	TRACE("自分のIPアドレス:%d.%d.%d.%d\n", ipData[0].d1, ipData[0].d2, ipData[0].d3, ipData[0].d4);
	TRACE("自分のIPアドレス:%d.%d.%d.%d\n", ipData[1].d1, ipData[1].d2, ipData[1].d3, ipData[1].d4);
	int mode;

	do {
		std::cout << "0の時は{ホスト}\n1の時は{ゲスト}\n2の時は{オフライン}\n";
		std::cin >> mode;
		if (mode == 0)
		{
			lpNetWork.SetNetWorkMode(NetWorkMode::HOST);
			upMode = UpMode::StartInit;
		}
		else if (mode == 1)
		{
			lpNetWork.SetNetWorkMode(NetWorkMode::GUEST);
			upMode = UpMode::SetHostIP;
		}
		else
		{
			if (mode != 2)
			{
				std::cout << "異常な数値\n";
			}
			lpNetWork.SetNetWorkMode(NetWorkMode::OFFLINE);
			init();
			upMode = UpMode::Play;
		}
	} while (mode < 0 || mode > 2);

	switch (lpNetWork.GetNetWorkMode())
	{
	case NetWorkMode::HOST:
		lpTMXMng.LoadTMX();
		std::cout << "ホストモード\nです";
		break;
	case NetWorkMode::GUEST:
		std::cout << "ゲストモード\nです";
		break;
	case NetWorkMode::OFFLINE:
		std::cout << "オフラインモード\nです";
		break;
	default:
		std::cout << "異常発生\n";
		break;
	}
	TRACE("状態は%dです。\n", lpNetWork.GetActive());
	
}

void LoginScene::SetHostIP(void)
{
	IPDATA hostIP;		// ホストのIP
	std::string ip;
	std::cout << "接続したいIPアドレスを入力して下さい。\n";
	std::cin >> ip;
	std::istringstream iss(ip);
	std::string str;
	std::vector<std::string> result;
	
	while (std::getline(iss, str, '.'))
	{
		result.push_back(str);
	}
	hostIP.d1 = std::atoi(result[0].c_str());
	hostIP.d2 = std::atoi(result[1].c_str());
	hostIP.d3 = std::atoi(result[2].c_str());
	hostIP.d4 = std::atoi(result[3].c_str());
	if (lpNetWork.ConnectHost(hostIP) == ActiveState::Init)
	{
		TRACE("接続完了。\n");
		upMode = UpMode::StartInit;
	}
}

void LoginScene::StartInit(void)
{
	if (lpNetWork.GetActive() == ActiveState::Init)
	{
		if (lpNetWork.GetNetWorkMode() == NetWorkMode::HOST)
		{
			
			lpNetWork.SendStanby();
			TRACE("初期化情報送信済み\nスタート信号待ち")
		}
		else
		{
			if (lpNetWork.GetRevStanby())
			{
				lpNetWork.SendStart();
			}
		}
	}
	if (lpNetWork.GetActive() == ActiveState::Stanby)
	{
		lpNetWork.GetRevStart();
	}
	if (lpNetWork.GetActive() == ActiveState::Play)
	{
		upMode = UpMode::Play;
	}
}

void LoginScene::Play(void)
{
	int lengthx = 0;
	int lengthy = 0;
	data.first = 0;
	data.second = 0;
	switch (lpNetWork.GetNetWorkMode())
	{
	case NetWorkMode::HOST:
		if (GetNetWorkDataLength(lpNetWork.GetHandle()) >= sizeof(data))
		{
			NetWorkRecv(lpNetWork.GetHandle(), &data, sizeof(data));
			posx += data.first;
			posy += data.second;
		}
		/*TRACE("%d", data);*/
		break;
	case NetWorkMode::GUEST:

		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
		{
			lengthy = -10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
		{
			lengthy = 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
		{
			lengthx = 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
		{
			lengthx = -10;
		}
		data.first = lengthx;
		data.second = lengthy;
		/*TRACE("%d", data);*/
		NetWorkSend(lpNetWork.GetHandle(), &data, sizeof(data));
		break;
	case NetWorkMode::OFFLINE:
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)
		{
			posy -= 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)
		{
			posy += 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT)
		{
			posx += 10;
		}
		if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)
		{
			posx -= 10;
		}
		break;
	default:
		std::cout << "異常発生\n";
		break;
	}
	
}
