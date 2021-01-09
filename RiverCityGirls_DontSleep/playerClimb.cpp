#include "stdafx.h"
#include "playerClimb.h"

void playerClimb::EnterState()
{
	_thisPl->changeImg("pl_climb", false);

	_thisPl->getObj().ani->init(_thisPl->getRefObj().img->getWidth(), _thisPl->getRefObj().img->getHeight(),
		_thisPl->getRefObj().img->getFrameWidth(), _thisPl->getRefObj().img->getFrameHeight());
	_thisPl->getObj().ani->setDefPlayFrame(false, true);

	_thisPl->getObj().ani->start();

	_thisPl->changePos(1555, _thisPl->getObj().pos.z, _thisPl->getObj().pos.y);
	
}

void playerClimb::UpdateState()
{
	//Ű�Է����϶���.
	
	switch (_thisPl->getInfo().moveDest)
	{
	case MOVE_DIRECTION::RIGHT:
	case MOVE_DIRECTION::LEFT :
		_thisPl->getObj().ani->pause();
	case MOVE_DIRECTION::UP:
		if (!KEY_M->isStayKeyDown(VK_UP)
			&& _thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->pause();
		if (KEY_M->isStayKeyDown(VK_UP)
			&& !_thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->start();
		break;
	case MOVE_DIRECTION::DOWN:
		if (!KEY_M->isStayKeyDown(VK_DOWN)
			&& _thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->pause();
		if (KEY_M->isStayKeyDown(VK_DOWN)
			&& !_thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->start();
		break;
	}
	//��Ʈ������ ��ٸ��ö󰡸� �ö󰡴»�ٸ��� ���º���
	if (KEY_M->isOnceKeyDown('J'))
		_thisPl->setState(PL_STATE::CLIMBTOP);

	//���Ʒ� ������
	lineMove(_thisPl->getInfo().speed);

	//��Ʈ������ ��ٸ� �������� �ٷ� ���º���
	if (KEY_M->isOnceKeyDown(VK_DOWN)
		&& _thisPl->getObj().pos.z>=930)
		_thisPl->setState(PL_STATE::IDLE);

	//��Ʈ������ ��ٸ� ���� �ö󰡸� �ٷ� ���º���
	if (KEY_M->isOnceKeyDown(VK_DOWN)
		&& _thisPl->getObj().pos.z <= 430)
		_thisPl->setState(PL_STATE::CLIMBTOP);



	//_thisPl->setState(PL_STATE::IDLE);
}

void playerClimb::ExitState()
{
}
