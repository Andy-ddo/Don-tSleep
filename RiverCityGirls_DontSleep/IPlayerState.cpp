#include "stdafx.h"
#include "IPlayerState.h"

//������Ʈ �Ͻ����� ���� 
bool IPlayerState::pauseUpdate()
{
	//Ű������ �Ұ����ϰ�� 
	if (!_thisPl->getInfo().isControl) return true;

	//�׿�
	else return false;
}

//������ ���࿩��
bool IPlayerState::isEndFrame(bool reverse)
{
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
	{
		//���� �����ӹ�ȣ�� ����ȣ�� ����������� ��
		if (reverse == false && _thisPl->getObj().img->getFrameX() == _thisPl->getObj().img->getMaxFrameX())
			return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() == 0)
			return true;

		return false;
	}
	case DIRECTION::RIGHT:
	{
		//���� �����ӹ�ȣ�� 0 ��ȣ�� ����������� ��
		if (reverse == false && _thisPl->getObj().img->getFrameX() == 0) return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() == _thisPl->getObj().img->getMaxFrameX())return true;
		return false;
	}
	}
}

void IPlayerState::walkPattern()
{
	//�ȱ�
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
}

void IPlayerState::basePattern()
{
	//�ȱ�
	walkPattern();

	//����
	if (KEY_M->isStayKeyDown('F'))_thisPl->setState(PL_STATE::GUARD);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO1);

}

//�����̵�
void IPlayerState::lineMove(float speed)
{	
	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -speed, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, speed, 0);
}

//�¿��̵�
void IPlayerState::crossMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-speed, 0, 0);
}
