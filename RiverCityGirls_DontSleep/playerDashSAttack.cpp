#include "stdafx.h"
#include "playerDashSAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerDashSAttack::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_dashSAttack", false);
	//Ű���� �Ұ�
	_thisPl->setIsControl(false);

	_isCollision = false;
}

void playerDashSAttack::UpdateState()
{
	RECT _temp;
	//���� ����
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (!_isCollision
			&&_thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj(),30)
			&&IntersectRect(&_temp, &_thisPl->getInfo().attackObj->rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{

			if (!_thisPl->getInfo().isAttack)
			{
				_thisPl->getInfo().isAttack = true;
				_isCollision = true;
			}
		}
	}

	//���⸦ ����߸�.
	dropWeapon();

	//�������� �� ���� ���� ���·� ���ư���
	if (isEndFrame(false)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	if (isEndFrame(false)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
	
	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

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
