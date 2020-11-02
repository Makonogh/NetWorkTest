#include "DxLib.h"
#include "HostState.h"

HostState::HostState()
{
	PreparationListenNetWork(portNum_);
	active_ = ActiveState::Wait;
}

HostState::~HostState()
{
}

bool HostState::Update(void)
{
	if (active_ == ActiveState::Wait)
	{
		netHandle_ = GetNewAcceptNetWork();
		if (netHandle_ != -1)
		{
			StopListenNetWork();
			active_ = ActiveState::Init;
		}
	}
	if (active_ == ActiveState::Play)
	{

	}
	return true;
}

//
//bool HostState::NetWorkConnectWait()
//{
//    while (!ProcessMessage())
//    {
//        netHandle_ = GetNewAcceptNetWork();
//        if (netHandle_ != -1) break;
//    }
//    StopListenNetWork();
//	return true;
//}
