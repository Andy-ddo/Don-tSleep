#include "stdafx.h"
#include "playerWait.h"

void playerWait::EnterState()
{
	_thisPl->changeImg("pl_wallet");
}

void playerWait::UpdateState()
{
	_thisPl->changeImg("pl_wallet");

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
