#pragma once
#include "IPlayerState.h"

class playerIdle :public IPlayerState
{
	float _stateTimer;	//���°� ����Ǵ� Ÿ�̸�
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

