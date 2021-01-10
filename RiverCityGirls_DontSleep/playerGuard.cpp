#include "stdafx.h"
#include "playerGuard.h"

void playerGuard::EnterState()
{
	_thisPl->changeImg("pl_guard",true);
	//Ű���� �Ұ��� ���·� ����
	_thisPl->setIsControl(false);
}

void playerGuard::UpdateState()
{
	//Ű�� �� ������ �⺻����
	if (!KEY_M->isStayKeyDown('F'))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerGuard::ExitState()
{
}
