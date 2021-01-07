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
	if (isEndFrame(false) 
		&&! KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)_thisPl->setState(PL_STATE::IDLE);

	if (isEndFrame(false)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)_thisPl->setState(PL_STATE::IDLE);
	
	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)_thisPl->setState(PL_STATE::RUN);

	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)_thisPl->setState(PL_STATE::RUN);

	//�̵�
	if (_thisPl->getInfo().dest == DIRECTION::LEFT
		&&_thisPl->getObj().img->getFrameX() <= _thisPl->getObj().img->getMaxFrameX()-10)
		_thisPl->movePos(-_thisPl->getInfo().speed*1.7, 0, 0);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT
		&&_thisPl->getObj().img->getFrameX() >= 10)
		_thisPl->movePos(_thisPl->getInfo().speed*1.7, 0, 0);
}

void playerDashSAttack::ExitState()
{
}
