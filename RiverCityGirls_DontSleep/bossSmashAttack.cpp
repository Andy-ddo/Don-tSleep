#include "stdafx.h"
#include "bossSmashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSmashAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_smash");
}

void bossSmashAttack::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getobj().pos.x > _thisBs->getPlayerAddress()->getObj().pos.x)
	{
		_thisBs->getIsInfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x - 10, _thisBs->getobj().pos.z, 20, 20);
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) �浹ó�� �ʿ�, �÷��̾� ��Ʈ? 
		//�չٴ� ���ú��� ���� �����
	}
}

void bossSmashAttack::ExitState()
{
	return;
	_thisBs->SetState(BS_STATE::IDLE);
}
