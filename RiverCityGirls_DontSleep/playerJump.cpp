#include "stdafx.h"
#include "playerJump.h"
#include "player.h"

void playerJump::EnterState()
{
	_thisPl->ChangeImg("pl_jump");
}

void playerJump::UpdateState()
{
	_thisPl->ChangeImg("pl_jump");

	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::JUMPATTACK);

}

void playerJump::ExitState()
{
}