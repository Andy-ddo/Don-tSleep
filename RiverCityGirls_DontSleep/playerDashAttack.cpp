#include "stdafx.h"
#include "playerDashAttack.h"
#include "player.h"

void playerDashAttack::EnterState()
{
	//������ȯ �Ұ�
	_thisPl->setIsConDest(false);
	
	tempTime = TIME_M->getWorldTime();
	_thisPl->ChangeImg("pl_dashAttack");

}

void playerDashAttack::UpdateState()
{
	_thisPl->ChangeImg("pl_dashAttack");
	//�ӽ�Ÿ�̸�..������ �����ӷ��� �ٵ��ư��� �����ҵ�!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);

	/*
	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (TIME_M->getWorldTime() - tempTime > .5f
		&& KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&&_thisPl->GetInfo().indexDest == PL_INDEX_DEST::RIGHT)_thisPl->SetState(PL_STATE::RUN);

	if (TIMEMANAGER->getWorldTime() - tempTime > .5f
		&& KEYMANAGER->isStayKeyDown(VK_LEFT)
		&&_thisPl->GetInfo().indexDest == PL_INDEX_DEST::LEFT)_thisPl->SetState(PL_STATE::RUN);
		
	//�̵�
	lineMove(_thisPl->GetInfo().speed / 1.5);
	crossMove(_thisPl->GetInfo().speed*1.5);
	*/
}

void playerDashAttack::ExitState()
{
}
