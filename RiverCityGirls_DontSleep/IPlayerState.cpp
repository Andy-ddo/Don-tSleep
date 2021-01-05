#include "stdafx.h"
#include "IPlayerState.h"

//업데이트 일시정지 유무 
bool IPlayerState::pauseUpdate()
{
	//키조작이 불가능일경우 
	if (!_thisPl->getInfo().isControl) return true;

	//그외
	else return false;
}

void IPlayerState::walkPattern()
{
	//걷기
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
}

void IPlayerState::basePattern()
{
	//걷기
	walkPattern();

	//가드
	if (KEY_M->isStayKeyDown('F'))_thisPl->setState(PL_STATE::GUARD);

	//약공격
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO1);

}

//상하이동
void IPlayerState::lineMove(float speed)
{	
	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -speed, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, speed, 0);
}

//좌우이동
void IPlayerState::crossMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-speed, 0, 0);
}
