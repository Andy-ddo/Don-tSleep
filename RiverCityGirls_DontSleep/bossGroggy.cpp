#include "stdafx.h"
#include "bossGroggy.h"
#include "Boss.h"

void bossGroggy::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_down");
}

void bossGroggy::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{
		return;	// �� �ð����� �ƹ��͵� ���ϰڴ�...(?)
	}
}

void bossGroggy::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}