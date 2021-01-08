#include "stdafx.h"
#include "bossDown.h"
#include "Boss.h"

void bossDown::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_down");
}

void bossDown::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{
		return;	// �� �ð����� �ƹ��͵� ���ϰڴ�...(?)
	}
}

void bossDown::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}
