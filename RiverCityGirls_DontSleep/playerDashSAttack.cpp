#include "stdafx.h"
#include "playerDashSAttack.h"

void playerDashSAttack::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_dashSAttack", false);
	//Ű���� �Ұ�
	_thisPl->setIsControl(false);
}

void playerDashSAttack::UpdateState()
{
	//�������� �� ���� ���� ���·� ���ư���
	//�忩�⿡ Ű�ȴ������������̶���� �߰������ؾ���
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	
	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)_thisPl->setState(PL_STATE::RUN);

	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)_thisPl->setState(PL_STATE::RUN);
		
	//�̵�
	/*
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);*/
}

void playerDashSAttack::ExitState()
{
}
