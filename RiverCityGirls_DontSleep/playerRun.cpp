#include "stdafx.h"
#include "playerRun.h"

void playerRun::EnterState()
{

	//�̹��� ����
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:_thisPl->changeImg("pl_run", true);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatRun", true);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}
	
	//Ű���� ����
	_thisPl->setIsControl(true);
	//������ȯ ����
	_thisPl->setIsConDest(true);
}

void playerRun::UpdateState()
{
	//Ű�� �� ������ �⺻����
	if (!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
	{
		KEY_M->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}

	//�̵�
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::DASHATTACK);

	//������
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::DASHSATTACK);


}

void playerRun::ExitState()
{
}
