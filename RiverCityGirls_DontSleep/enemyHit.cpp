#include "stdafx.h"
#include "enemyHit.h"
#include "Enemy.h"


void enemyHit::EnterState()
{
	_thisEn->SetImage();
}

void enemyHit::UpdateState()
{
	//HIT�� ���°� ������.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyHit::ExitState()
{
}
