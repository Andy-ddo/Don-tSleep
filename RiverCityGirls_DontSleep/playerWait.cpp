#include "stdafx.h"
#include "playerWait.h"
#include "player.h"

void playerWait::EnterState()
{
	_thisPl->ChangeImg("pl_wallet");
}

void playerWait::UpdateState()
{
	_thisPl->ChangeImg("pl_wallet");

	if(EVENT_M->isEvent())
	//�⺻����
	basePattern();

	//������
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);

}

void playerWait::ExitState()
{
}
