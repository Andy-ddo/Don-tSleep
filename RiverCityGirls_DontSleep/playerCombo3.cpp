#include "stdafx.h"
#include "playerCombo3.h"
#include "player.h"

void playerCombo3::EnterState()
{
	_thisPl->changeImg("pl_comboAttack3");
	tempTime = TIME_M->getWorldTime();
	//�������� ���ϴ� ���·� ����
	_thisPl->setIsConDest(false);
}

void playerCombo3::UpdateState()
{
	_thisPl->changeImg("pl_comboAttack3");

	//�ӽ�Ÿ�̸�..������ �����ӷ��� �ٵ��ư��� �����ҵ�!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);

	//�⺻ ����
	basePattern();
}

void playerCombo3::ExitState()
{
}
