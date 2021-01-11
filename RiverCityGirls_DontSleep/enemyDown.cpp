#include "stdafx.h"
#include "enemyDown.h"
#include "Enemy.h"

void enemyDown::EnterState()
{
	_thisEn->SetImage();
}

void enemyDown::UpdateState()
{
	LookAtPlayer();

	//HIT�� ���°� ������.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyDown::ExitState()
{
}
