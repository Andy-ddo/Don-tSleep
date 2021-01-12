#include "stdafx.h"
#include "bossSmashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSmashAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_smash");

	LookatPlayer();
	ResetFrame();
}

void bossSmashAttack::UpdateState()
{

	Attack();

	/*if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getInfo().dest == DIRECTION ::LEFT)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x - 50, _thisBs->getObj()->pos.z, 50, 50);
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) �浹ó�� �ʿ�, �÷��̾� ��Ʈ? 
		//�չٴ� ���ú��� ���� �����
	}

	else if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x + 50, _thisBs->getObj()->pos.z, 50, 50);
		RECT _temp;
	}*/
}

void bossSmashAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
