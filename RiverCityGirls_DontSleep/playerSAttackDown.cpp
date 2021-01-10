#include "stdafx.h"
#include "playerSAttackDown.h"

void playerSAttackDown::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_sAttackDown", true);	

	//Ű�Է� ����
	_thisPl->setIsControl(false);

	//����Ÿ���� �������� ����
	dropWeapon();

}

void playerSAttackDown::UpdateState()
{
	//���ݿ��� üũ
	checkEnemy();

	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttackDown::ExitState()
{
}
