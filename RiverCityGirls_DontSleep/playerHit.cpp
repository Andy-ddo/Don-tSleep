#include "stdafx.h"
#include "playerHit.h"


void playerHit::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_hit", false);


	//���ⶳ��߸���
	dropWeapon();
}

void playerHit::UpdateState()
{
}

void playerHit::ExitState()
{
}
