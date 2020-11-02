#pragma once
#include "NetWorkState.h"
class HostState :
	public NetWorkState
{
public:
	HostState();
	~HostState();
	NetWorkMode GetMode(void) override { return NetWorkMode::HOST; };
	bool Update(void) override;
};

