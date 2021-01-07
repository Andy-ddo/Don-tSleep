#include "stdafx.h"
#include "playerSAttack.h"

void playerSAttack::EnterState()
{
	//�̹��� ����
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_sAttack", false);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatThrow", false);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}
	_thisPl->setIsControl(false);
}

void playerSAttack::UpdateState()
{
	//����Ÿ���� �������� ����
	if(_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)_thisPl->setWeaponType(WEAPON_TYPE::NONE);
	if (isEndFrame(false))
	{
		//Ű���� ������ ���·� ����
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttack::ExitState()
{
}
