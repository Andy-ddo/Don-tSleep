#include "stdafx.h"
#include "playerSAttack.h"

void playerSAttack::EnterState()
{
	_thisPl->setIsControl(false);
	_thisPl->changeImg("pl_SAttack");

	tempTime = TIME_M->getWorldTime();
}

void playerSAttack::UpdateState()
{
	_thisPl->changeImg("pl_SAttack");

	//�ӽ�Ÿ�̸�..������ �����ӷ��� �ٵ��ư��� �����ҵ�!
	if(TIME_M->getWorldTime()-tempTime>.5f)_thisPl->setState(PL_STATE::IDLE);
	
}

void playerSAttack::ExitState()
{
}
