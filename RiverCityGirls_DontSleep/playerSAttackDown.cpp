#include "stdafx.h"
#include "playerSAttackDown.h"

void playerSAttackDown::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_sAttackDown", true);	

	//Ű�Է� ����
	_thisPl->setIsControl(false);

	//����Ÿ���� �������� ����
	if (_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)_thisPl->setWeaponType(WEAPON_TYPE::NONE);


}

void playerSAttackDown::UpdateState()
{
	//���ݿ��� üũ
	checkAttack();

	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttackDown::ExitState()
{
}
