#pragma once
#include "IPlayerState.h"

class playerWalk :public IPlayerState
{
	float _startTime;		//Ű�Է½ð�üũ�� ���� ����Ÿ��
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

