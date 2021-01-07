#include "stdafx.h"
#include "playerJump.h"

void playerJump::EnterState()
{
	//�̹��� ����
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_jump", false); break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatJump", false);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}
	
}

void playerJump::UpdateState()
{
	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed/2);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::JUMPATTACK);

}

void playerJump::ExitState()
{
}
