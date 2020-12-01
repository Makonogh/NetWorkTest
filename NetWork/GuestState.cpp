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
	netHandle_ = ConnectNetWork(hostIP,portNum_);
	if (netHandle_ != -1)
	{
		playerlist_.push_back({ 0,netHandle_ });
		active_ = ActiveState::Init;
	}
	return active_;
}
