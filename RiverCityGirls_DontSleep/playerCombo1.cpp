#include "stdafx.h"
#include "playerCombo1.h"

void playerCombo1::EnterState()
{
	_thisPl->changeImg("pl_comboAttack1", false);
	tempTime = TIME_M->getWorldTime();
}

void playerCombo1::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
	//�������� ������ ���ݷ�Ʈ�� ���� �浹�ߴ��� Ȯ���ϰ� �������� ��! �����ϸ�ɰŰ�������..

	//����Ű ������ 2�޺� + �ڸ��Ϳ� �浹�� �־���ҵ�
	if(KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO2);

	//�⺻ ����
	basePattern();
}

void playerCombo1::ExitState()
{
}
