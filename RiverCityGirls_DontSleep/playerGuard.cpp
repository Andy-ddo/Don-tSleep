#include "stdafx.h"
#include "playerGuard.h"
#include "player.h"

void playerGuard::EnterState()
{
	_thisPl->ChangeImg("pl_guard");
	//Ű���� �Ұ��� ���·� ����
	_thisPl->setIsControl(false);
}

void playerGuard::UpdateState()
{
	_thisPl->ChangeImg("pl_guard");

	//Ű�� �� ������ �⺻����
	if (!KEY_M->isStayKeyDown(VK_SPACE))
	{
		KEY_M->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerGuard::ExitState()
{
}
