#pragma once
#include "IPlayerState.h"

class playerCombo2 : public IPlayerState
{
	//공격충돌용
	RECT _temp;
	bool _isCollision;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

