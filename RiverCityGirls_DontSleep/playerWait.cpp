#include "stdafx.h"
#include "playerWait.h"

void playerWait::EnterState()
{
	_thisPl->changeImg("pl_wait",false);
}

void playerWait::UpdateState()
{
	//�⺻����
	basePattern();

	//������
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);

}

void playerWait::ExitState()
{
}
