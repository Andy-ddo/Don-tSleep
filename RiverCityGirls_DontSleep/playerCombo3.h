#pragma once
#include "IPlayerState.h"

class playerCombo3: public IPlayerState
{
	float tempTime;	//�̹������� ��� �ӽ�Ÿ�̸�
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

