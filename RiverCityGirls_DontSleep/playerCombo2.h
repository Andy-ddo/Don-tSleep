#pragma once
#include "IPlayerState.h"

class playerCombo2 : public IPlayerState
{
	//�����浹��
	RECT temp;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

