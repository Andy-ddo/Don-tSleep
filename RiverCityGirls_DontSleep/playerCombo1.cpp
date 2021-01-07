#include "stdafx.h"
#include "playerCombo1.h"

void playerCombo1::EnterState()
{
	//�̹��� ����
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_comboAttack1", false);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatAttack", false);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}
}

void playerCombo1::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
	//�������� ������ ���ݷ�Ʈ�� ���� �浹�ߴ��� Ȯ���ϰ� �������� ��! �����ϸ�ɰŰ�������..

	//���º��� - ����Ű ������ 2�޺� + �ڸ��Ϳ� �浹�� �־���ҵ�
	if (KEY_M->isOnceKeyDownV('S'))
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->setState(PL_STATE::COMBO2);	break;
	case WEAPON_TYPE::BAT:	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}

	
	

	//�⺻ ����
	basePattern();
}

void playerCombo1::ExitState()
{
}
