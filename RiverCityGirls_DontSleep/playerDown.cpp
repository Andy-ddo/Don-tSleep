#include "stdafx.h"
#include "playerDown.h"

void playerDown::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_down", false);
}

void playerDown::UpdateState()
{
	if (isEndFrame(false) && !_thisPl->getInfo().isDead)_thisPl->setState(PL_STATE::STAND);
	if (isEndFrame(false) && _thisPl->getInfo().isDead)_thisPl->setState(PL_STATE::DEAD);
}

void playerDown::ExitState()
{
}
