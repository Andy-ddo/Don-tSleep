#include "stdafx.h"
#include "enemyAttack2.h"
#include "Enemy.h"

void enemyAttack2::EnterState()
{
	_thisEn->SetImage();
}

void enemyAttack2::UpdateState()
{
	LookAtPlayer();
	Attack();

	//ATTACK2�� ���°� ������.
	if (endFrame())
	{
		//������ ������.
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
			_thisEn->SetState(EN_STATE::EN_ATTACK3);
		else _thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyAttack2::ExitState()
{
	_thisEn->getInfo().isAttack = false;
}
