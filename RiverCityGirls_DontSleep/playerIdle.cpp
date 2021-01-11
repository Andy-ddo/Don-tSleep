#include "stdafx.h"
#include "playerIdle.h"

void playerIdle::EnterState()
{
	//�̹��� ����
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatIdle", true);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}

	}
	else _thisPl->changeImg("pl_idle", true);

	//���������� ������ ���·� ����
	_thisPl->getInfo().isConDest = true;
	//���� ���� �ƴ�
	_thisPl->getInfo().isAttack = false;
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

	/*���Ⱑ �Ѿƴٴ�,...;;
	if (_thisPl->getInfo().attackObj)
	{
	_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
	_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
	_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;
	}*/

	//�ݱ�
	if (KEY_M->isOnceKeyDownV('E')) { _thisPl->setState(PL_STATE::PICK); }
		
	
}

void playerIdle::ExitState()
{
}
