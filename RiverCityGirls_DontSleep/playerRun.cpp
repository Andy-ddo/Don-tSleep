#include "stdafx.h"
#include "playerRun.h"
#include "player.h"

void playerRun::EnterState()
{
	_thisPl->changeImg("pl_run");
}

void playerRun::UpdateState()
{
	_thisPl->changeImg("pl_run");

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
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(_thisPl->getInfo().speed*1.5, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-_thisPl->getInfo().speed*1.5, 0, 0);

	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -_thisPl->getInfo().speed / 1.5, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, _thisPl->getInfo().speed / 1.5, 0);


}

void playerRun::ExitState()
{
}
