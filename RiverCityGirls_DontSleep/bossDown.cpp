#include "stdafx.h"
#include "bossDown.h"
#include "Boss.h"

void bossDown::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_groggy");

	if (_thisBs->getdest() == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}

	else if (_thisBs->getdest() == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void bossDown::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 2.5f)
	{
		_thisBs->SetState(BS_STATE::STANDATTACK);
	}
	
}

void bossDown::ExitState()
{
	_thisBs->SetState(BS_STATE::STANDATTACK);
}
