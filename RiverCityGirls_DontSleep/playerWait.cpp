#include "stdafx.h"
#include "playerWait.h"
#include "player.h"

void playerWait::EnterState()
{
	_thisPl->changeImg("pl_wallet");
}

void playerWait::UpdateState()
{
	_thisPl->changeImg("pl_wallet");

	//����Ű������ ���º�ȯ
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
}

void playerWait::ExitState()
{
}
