#include "stdafx.h"
#include "playerWalk.h"
#include "player.h"

void playerWalk::EnterState()
{
	_thisPl->ChangeImg("pl_walk");
	_startTime = TIME_M->getWorldTime();
	//���⺯�氡�ɻ��·� ��ȯ
	_thisPl->setIsConDest(true);
}

void playerWalk::UpdateState()
{
	_thisPl->ChangeImg("pl_walk");
	/*
	//�ѹ��� ������ �뽬
	if (_thisPl->GetInfo().dest == PL_DEST::LEFT &&
		KEYMANAGER->isOnceKeyDownV(VK_LEFT))_thisPl->setState(PL_STATE::RUN);

	if (_thisPl->GetInfo().dest == PL_DEST::RIGHT &&
		KEYMANAGER->isOnceKeyDownV(VK_RIGHT))_thisPl->setState(PL_STATE::RUN);

	//Ű�� ������ ������ �⺻ ����
	
	if (TIME_M->getWorldTime() - _startTime >0.25f
		&&!KEYMANAGER->isStayKeyDown(VK_LEFT)
		&& !KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& !KEYMANAGER->isStayKeyDown(VK_UP)
		&& !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		KEYMANAGER->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}
	


	//�̵�
	lineMove(_thisPl->GetInfo().speed / 2);
	crossMove(_thisPl->GetInfo().speed);*/
}

void playerWalk::ExitState()
{
}
