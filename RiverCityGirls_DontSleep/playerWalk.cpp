#include "stdafx.h"
#include "playerWalk.h"

void playerWalk::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_walk",true);
	_startTime = TIME_M->getWorldTime();
	//���⺯�氡�ɻ��·� ��ȯ
	_thisPl->setIsConDest(true);
}

void playerWalk::UpdateState()
{
	//�ѹ��� ������ �뽬
	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::LEFT &&
		KEY_M->isOnceKeyDownV(VK_LEFT))_thisPl->setState(PL_STATE::RUN);

	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::RIGHT &&
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
	lineMove(_thisPl->getInfo().speed / 2);
	crossMove(_thisPl->getInfo().speed);
}

void playerWalk::ExitState()
{
}
