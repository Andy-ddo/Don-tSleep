#pragma once
#include "IPlayerState.h"

class playerJumpAttack :public IPlayerState
{
	//����������
	bool _isCollsion;
	RECT _temp;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

