#include "stdafx.h"
#include "playerJumpAttack.h"

void playerJumpAttack::EnterState()
{
	//���� ���� �Ұ�
	_thisPl->setIsConDest(false);

	_thisPl->changeImg("pl_jumpAttack",false);
}

void playerJumpAttack::UpdateState()
{
	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed / 2);

}

void playerJumpAttack::ExitState()
{
}
