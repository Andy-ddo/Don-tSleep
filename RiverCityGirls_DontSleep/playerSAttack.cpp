#include "stdafx.h"
#include "playerSAttack.h"
#include "player.h"

void playerSAttack::EnterState()
{
	_thisPl->setIsControl(false);
	_thisPl->ChangeImg("pl_SAttack");

	tempTime = TIME_M->getWorldTime();
}

void playerSAttack::UpdateState()
{
	_thisPl->ChangeImg("pl_SAttack");

	//�ӽ�Ÿ�̸�..������ �����ӷ��� �ٵ��ư��� �����ҵ�!
	if(TIME_M->getWorldTime()-tempTime>.5f)_thisPl->setState(PL_STATE::IDLE);
	
}

void playerSAttack::ExitState()
{
}