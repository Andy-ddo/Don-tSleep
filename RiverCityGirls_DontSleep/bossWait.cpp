#include "stdafx.h"
#include "bossWait.h"

void bossWait::EnterState()
{
	_count = 0;
	_count++;	
	
	_thisBs->ChangeImg("Bs_idle");
}

void bossWait::UpdateState()
{
	

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
