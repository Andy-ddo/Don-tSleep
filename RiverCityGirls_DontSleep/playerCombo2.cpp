#include "stdafx.h"
#include "playerCombo2.h"

void playerCombo2::EnterState()
{
	_thisPl->changeImg("pl_comboAttack2");
	tempTime = TIME_M->getWorldTime();
	//�������� ���ϴ� ���·� ����
	_thisPl->setIsConDest(false);
}

void playerCombo2::UpdateState()
{
	//�ӽ�Ÿ�̸�..������ �����ӷ��� �ٵ��ư��� �����ҵ�!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);

	//����Ű ������ 2�޺� + �ڸ��Ϳ� �浹�� �־���ҵ�
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO3);

	//�⺻ ����
	basePattern();
}

void playerCombo2::ExitState()
{
}
