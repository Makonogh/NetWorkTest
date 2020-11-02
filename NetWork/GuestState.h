#pragma once
#include "NetWorkState.h"
class GuestState :
	public NetWorkState
{
public:
	GuestState();
	~GuestState();
	NetWorkMode GetMode(void) override { return NetWorkMode::GUEST; } ; 
	ActiveState ConnectHost(IPDATA hostIP) override;
};

