#include "stdafx.h"
#include "bossWait.h"
#include "Boss.h"
#include "Player.h"

void bossWait::EnterState()
{
	_count = 0;
	_count++;	
	
	_thisBs->ChangeImg("Bs_idle");
	
}

void bossWait::UpdateState()
{
	if (_count % 4 == 0)
	{	
		if (!_thisBs->getIsAttack() && !_thisBs->getIsMove() && !_thisBs->getIsPhase())

		_thisBs->getIsWait();
		_thisBs->ChangeImg("Bs_idle");
	}

	else
	{
		!_thisBs->getIsWait();
	}

	/*	1. slab attack 
		2. elbow attack
		3. meteor attack
		4. dash attack
		5. smash attack
		6. bsss block
		���� ���� �ൿ ��ȭ�� �ܰ�*/
		
}

void bossWait::ExitState()
{
}
