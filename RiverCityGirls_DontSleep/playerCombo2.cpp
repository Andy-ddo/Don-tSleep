#include "stdafx.h"
#include "playerCombo2.h"

void playerCombo2::EnterState()
{
	_thisPl->changeImg("pl_comboAttack2", false);
	//�������� ���ϴ� ���·� ����
	_thisPl->setIsConDest(false);
}

void playerCombo2::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	//����Ű ������ 2�޺� + �ڸ��Ϳ� �浹�� �־���ҵ�
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO3);

	//�⺻ ����
	basePattern();
}

void playerCombo2::ExitState()
{
}
