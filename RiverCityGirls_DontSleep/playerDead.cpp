#include "stdafx.h"
#include "playerDead.h"


void playerDead::EnterState()
{
	//���ⶳ��߸���
	dropWeapon();

	//�Ѿ����־����� �ٷ� �����̹����� ����
	if (_thisPl->getInfo().preState == PL_STATE::DOWN)
	_thisPl->changeImg("pl_dead", false);

	//���
	_thisPl->getInfo().isDead = true;

	//Ű���� �Ұ�
	_thisPl->setIsControl(false);
}

void playerDead::UpdateState()
{
	//�Ѿ������� �ʾҴٸ� �Ѿ�߸�
	if (_thisPl->getInfo().preState != PL_STATE::DOWN )
		_thisPl->setState(PL_STATE::DOWN);
}

void playerDead::ExitState()
{
}
