#include "stdafx.h"
#include "playerGuard.h"
#include "Player.h"

void playerGuard::EnterState()
{
	_thisPl->changeImg("pl_guard");
	//Ű���� �Ұ��� ���·� ����
	_thisPl->setIsControl(false);
}

void playerGuard::UpdateState()
{
	_thisPl->changeImg("pl_guard");

	//Ű�� �� ������ �⺻����
	if (!KEY_M->isStayKeyDown('F'))
	{
		KEY_M->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerGuard::ExitState()
{
}
