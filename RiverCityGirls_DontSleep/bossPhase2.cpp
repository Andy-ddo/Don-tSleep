#include "stdafx.h"
#include "bossPhase2.h"
#include "Boss.h"
#include "Player.h"

void bossPhase2::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_phase");
	_thisBs->setIsphase(true);
	LookatPlayer();
	ResetFrame();
}

void bossPhase2::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.4f && _thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);
		EFFECT_M->play("Bss_howling",_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z);
	}

	if (TIME_M->getWorldTime() - _enterTime > 3.0f)
	{		
		_thisBs->SetState(BS_STATE::WAIT);
	}
}

void bossPhase2::ExitState()
{
	_thisBs->SetState(BS_STATE::WAIT);
	_thisBs->setIsphase(true);
	EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);
}
