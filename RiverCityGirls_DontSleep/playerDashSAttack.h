#pragma once
#include "IPlayerState.h"

class playerDashSAttack : public IPlayerState
{
	//����������
	bool _isCollsion;
	RECT _temp;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

