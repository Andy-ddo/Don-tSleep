#include "stdafx.h"
#include "playerCombo1.h"
#include "player.h"

void playerCombo1::EnterState()
{
	_thisPl->changeImg("pl_comboAttack1");
	tempTime = TIME_M->getWorldTime();
	//�������� ���ϴ� ���·� ����
	_thisPl->setIsConDest(false);
}

void playerCombo1::UpdateState()
{
	_thisPl->changeImg("pl_comboAttack1");

	//�ӽ�Ÿ�̸�..������ �����ӷ��� �ٵ��ư��� �����ҵ�!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);

	//����Ű ������ 2�޺� + �ڸ��Ϳ� �浹�� �־���ҵ�
	if(KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO2);

	//�⺻ ����
	basePattern();
}

void playerCombo1::ExitState()
{
}
