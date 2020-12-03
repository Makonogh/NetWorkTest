#include "DxLib.h"
#include "GuestState.h"

GuestState::GuestState()
{
	active_ = ActiveState::Non;
}

GuestState::~GuestState()
{
}

ActiveState GuestState::ConnectHost(IPDATA hostIP)
{
	auto netHandle_ = ConnectNetWork(hostIP,portNum_);
	if (netHandle_ != -1)
	{
		PlayerBundle player = { netHandle_,0,false };
		playerlist_.emplace_back(player);
		active_ = ActiveState::Init;
	}
	return active_;
}
