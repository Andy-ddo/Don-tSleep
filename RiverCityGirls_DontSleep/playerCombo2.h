#pragma once
#include "IPlayerState.h"
#include "player.h"

class playerCombo2 : public IPlayerState
{
	float tempTime;	//�̹������� ��� �ӽ�Ÿ�̸�
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
