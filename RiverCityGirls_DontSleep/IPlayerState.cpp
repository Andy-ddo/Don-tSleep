#include "stdafx.h"
#include "IPlayerState.h"
#include "Player.h"

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
		_thisPl->MovePos(0, -speed, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->MovePos(0, speed, 0);
}

//�¿��̵�
void IPlayerState::crossMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->MovePos(speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->MovePos(-speed, 0, 0);
}
