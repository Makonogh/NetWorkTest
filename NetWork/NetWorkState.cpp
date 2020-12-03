#include "DxLib.h"
#include "NetWorkState.h"

NetWorkState::NetWorkState()
{
	active_ = ActiveState::OFFLINE;
}

NetWorkState::~NetWorkState()
{
}

ActiveState NetWorkState::GetActive_(void)
{
	return active_;
}

ActiveState NetWorkState::ConnectHost(IPDATA hostIP)
{
	return active_;
}

bool NetWorkState::Update()
{
	return false;
}

bool NetWorkState::SetActive(ActiveState active)
{
	active_ = active;
	return false;
}

bool NetWorkState::CloseNetWork(void)
{
	return false;
}

ListInt& NetWorkState::GetPlayerList()
{
	return playerlist_;
}
