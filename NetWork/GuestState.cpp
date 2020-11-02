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
	if (netHandle_ >= 0)
	{
		active_ = ActiveState::Init;
	}

	return active_;
}
