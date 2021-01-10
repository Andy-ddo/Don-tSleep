#include "stdafx.h"
#include "playerDashAttack.h"

void playerDashAttack::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_dashAttack", true);
	//Ű���� �Ұ�
	_thisPl->setIsControl(false);
	//���ݿ���
	checkEnemy();
}

void playerDashAttack::UpdateState()
{
	//�������� 1��
	_thisPl->getInfo().isAttack = false;
	//���⸦ ����߸�.
	dropWeapon();

	//�������� �� ���� ���� ���·� ���ư���
	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}
	//�̵�
	if (_thisPl->getInfo().dest == DIRECTION::LEFT)
		_thisPl->movePos(-_thisPl->getInfo().speed*1.2, 0, 0);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT)
		_thisPl->movePos(_thisPl->getInfo().speed*1.2, 0, 0);
}

void playerDashAttack::ExitState()
{
}
