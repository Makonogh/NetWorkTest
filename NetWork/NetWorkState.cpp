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

int NetWorkState::GetnetHandle(void)
{
	return netHandle_;
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
