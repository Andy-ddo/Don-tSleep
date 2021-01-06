#include "stdafx.h"
#include "playerRun.h"

void playerRun::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_run",true);
}

void playerRun::UpdateState()
{
	//키를 안 누르면 기본상태
	if (!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
	{
		KEY_M->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}

	//이동
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);

	//약공격
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::DASHATTACK);

	//강공격
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::DASHSATTACK);


}

void playerRun::ExitState()
{
}
