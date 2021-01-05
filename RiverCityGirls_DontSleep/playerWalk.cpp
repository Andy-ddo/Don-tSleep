#include "stdafx.h"
#include "playerWalk.h"
#include "player.h"

void playerWalk::EnterState()
{
	_thisPl->changeImg("pl_walk");
	_startTime = TIME_M->getWorldTime();
}

void playerWalk::UpdateState()
{
	_thisPl->changeImg("pl_walk");

	//�ѹ��� ������ �뽬
	/*
	if (_thisPl->GetInfo().dest == PL_DEST::LEFT &&
		KEYMANAGER->isOnceKeyDownV(VK_LEFT))_thisPl->SetState(PL_STATE::RUN);

	if (_thisPl->GetInfo().dest == PL_DEST::RIGHT &&
		KEYMANAGER->isOnceKeyDownV(VK_RIGHT))_thisPl->SetState(PL_STATE::RUN);*/



	//�ѹ��� ������ �뽬
	if (
		KEY_M->isOnceKeyDownV(VK_LEFT))_thisPl->setState(PL_STATE::RUN);

	if (
		KEY_M->isOnceKeyDownV(VK_RIGHT))_thisPl->setState(PL_STATE::RUN);



	//Ű�� ������ ������ �⺻ ����
	
	if (TIME_M->getWorldTime() - _startTime >0.25f
		&&!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
	{
		KEY_M->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}
	


	//�̵�
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(_thisPl->getInfo().speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-_thisPl->getInfo().speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -_thisPl->getInfo().speed/2, 0);
	
	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, _thisPl->getInfo().speed / 2, 0);

}

void playerWalk::ExitState()
{
}
