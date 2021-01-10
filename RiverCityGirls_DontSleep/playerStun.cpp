#include "stdafx.h"
#include "playerStun.h"

void playerStun::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_stun", true);
	//Ű���ۺҰ�
	_thisPl->setIsControl(false);

	_stateTimer = TIME_M->getWorldTime();
}

void playerStun::UpdateState()
{
	if (TIME_M->getWorldTime()- _stateTimer >1.5f)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerStun::ExitState()
{
}
