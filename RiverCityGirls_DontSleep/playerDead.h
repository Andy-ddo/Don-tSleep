#pragma once
#include "IPlayerState.h"

class playerDead : public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

