#include "stdafx.h"
#include "playerJumpAttack.h"

void playerJumpAttack::EnterState()
{
	//���� ���� �Ұ�
	_thisPl->setIsConDest(false);

	_thisPl->ChangeImg("pl_jumpAttack");
}

void playerJumpAttack::UpdateState()
{
	//�̵�
	//crossMove(_thisPl->GetInfo().speed*1.2);
}

void playerJumpAttack::ExitState()
{
}
