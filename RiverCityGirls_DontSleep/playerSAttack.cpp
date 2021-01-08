#include "stdafx.h"
#include "playerSAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerSAttack::EnterState()
{
	//����� ���¸� ������� ���º���
	if (_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)
	{
		_thisPl->setState(PL_STATE::THROW);
		return;
	}
	//�̹��� ����
	_thisPl->changeImg("pl_sAttack", false);	
	
	//Ű�Է� ����
	_thisPl->setIsControl(false);

	
	//���ݿ��� üũ
	checkAttack();
}

void playerSAttack::UpdateState()
{
	//�������� 1��
	_thisPl->SetIsAttack(false);

	if (isEndFrame(false))
	{
		//Ű���� ������ ���·� ����
		_thisPl->setIsControl(true);

		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttack::ExitState()
{
}
