#include "stdafx.h"
#include "playerDashSAttack.h"
#include "player.h"


void playerDashSAttack::EnterState()
{
	//������ȯ �Ұ�
	_thisPl->setIsConDest(false);

	tempTime = TIME_M->getWorldTime();
	_thisPl->ChangeImg("pl_dashSAttack");
}

void playerDashSAttack::UpdateState()
{
	_thisPl->ChangeImg("pl_dashSAttack");
	//�ӽ�Ÿ�̸�..������ �����ӷ��� �ٵ��ư��� �����ҵ�!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);
	
	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (TIME_M->getWorldTime() - tempTime > .5f
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)_thisPl->setState(PL_STATE::RUN);

	if (TIME_M->getWorldTime() - tempTime > .5f
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)_thisPl->setState(PL_STATE::RUN);

	//�̵�
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);
}

void playerDashSAttack::ExitState()
{
}