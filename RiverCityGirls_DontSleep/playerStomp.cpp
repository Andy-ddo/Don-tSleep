#include "stdafx.h"
#include "playerStomp.h"

void playerStomp::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_stomp", true);

	//����Ÿ���� �������� ����
	dropWeapon();

	//���ݿ��� üũ
	checkEnemy();

}

void playerStomp::UpdateState()
{
	//����������
	_thisPl->getInfo().isAttack = false;
	if (isEndFrame(true))
	{

		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerStomp::ExitState()
{
}
