#include "stdafx.h"
#include "playerJumpAttack.h"
#include "Player.h"

void playerJumpAttack::EnterState()
{
	//���� ���� �Ұ�
	_thisPl->setIsConDest(false);

	_thisPl->changeImg("pl_jumpAttack");
}

void playerJumpAttack::UpdateState()
{
	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);
}

void playerJumpAttack::ExitState()
{
}
