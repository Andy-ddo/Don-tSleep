#include "stdafx.h"
#include "playerWait.h"
#include "Player.h"

void playerWait::EnterState()
{
	_thisPl->ChangeImg("pl_wallet");
}

void playerWait::UpdateState()
{
	_thisPl->ChangeImg("pl_wallet");

	//������Ʈ���� ����
	if (pauseUpdate())return;

	//�⺻����
	basePattern();

	//������
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);

}

void playerWait::ExitState()
{
}
