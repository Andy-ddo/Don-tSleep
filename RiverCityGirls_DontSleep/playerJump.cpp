#include "stdafx.h"
#include "playerJump.h"
#include "Player.h"

void playerJump::EnterState()
{
	_thisPl->changeImg("pl_jump");
}

void playerJump::UpdateState()
{
	_thisPl->changeImg("pl_jump");

	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::JUMPATTACK);

}

void playerJump::ExitState()
{
}
