#include "stdafx.h"
#include "playerIdle.h"

void playerIdle::EnterState()
{
	//�̹��� ����
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_idle", true);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatIdle", true);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}

	//���������� ������ ���·� ����
	_thisPl->setIsConDest(true);
	//���� ���� �ƴ�
	_thisPl->SetIsAttack(false);

	//Ÿ�̸Ӹ� ����Ÿ�̸ӷ� ���缭 �ʱ�ȭ
	_stateTimer = TIME_M->getWorldTime();

	//ŰĿ�Ǵ� ���� ���
	KEY_M->clearVKey();
	
}

void playerIdle::UpdateState()
{
	//�����ð����� �������� ������ ��ٸ� ���·� ��ȯ
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)_thisPl->setState(PL_STATE::WAIT);
	//������Ʈ ���� ����
	if (pauseUpdate())return;

	
	//�⺻ ����
	basePattern();
	
	//������
	sAttack();
		
	
}

void playerIdle::ExitState()
{
}
