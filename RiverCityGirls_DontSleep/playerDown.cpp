#include "stdafx.h"
#include "playerDown.h"

void playerDown::EnterState()
{
	//�̹û��·� �����
	_thisPl->getInfo().isImmune = true;
	_thisPl->getRefObj().alpha = 180;

	//�̹�������
	_thisPl->changeImg("pl_down", false);

	//���ⶳ��߸���
	dropWeapon();

	_thisPl->setIsControl(false);
}

void playerDown::UpdateState()
{
	if (isEndFrame(false) && !_thisPl->getInfo().isDead)
	{
		_thisPl->setState(PL_STATE::STAND);
		_thisPl->setIsControl(true);
	}

	if (isEndFrame(false) && _thisPl->getInfo().isDead)_thisPl->setState(PL_STATE::DEAD);
}

void playerDown::ExitState()
{
	_thisPl->setIsControl(true);

}
