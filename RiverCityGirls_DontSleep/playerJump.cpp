#include "stdafx.h"
#include "playerJump.h"

void playerJump::EnterState()
{
	_thisPl->changeImg("pl_jump",false);
}

void playerJump::UpdateState()
{
	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed/2);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::JUMPATTACK);

}

void playerJump::ExitState()
{
}
