#include "stdafx.h"
#include "playerStomp.h"

void playerStomp::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_stomp", true);

	//����Ÿ���� �������� ����
	if (_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)_thisPl->setWeaponType(WEAPON_TYPE::NONE);

	//���ݿ��� üũ
	checkAttack();

}

void playerStomp::UpdateState()
{
	//����������
	_thisPl->SetIsAttack(false);

	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerStomp::ExitState()
{
}
