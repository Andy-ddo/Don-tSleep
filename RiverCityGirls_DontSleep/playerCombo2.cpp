#include "stdafx.h"
#include "playerCombo2.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo2::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_comboAttack2", false);
	_isCollision = false;

	//���ݿ���
	checkAttack();
}

void playerCombo2::UpdateState()
{
	_thisPl->SetIsAttack(false);
	//����Ű�Է� �޾Ƽ� ���Ϳ� ����
	if (KEY_M->isOnceKeyDownV('S'));

	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		//������ ù�浹��
		if (!_isCollision
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{
			_isCollision = true;
		}

		//������ 2�޺� ������ ���
		if (isEndFrame(false)
			&& KEY_M->getVKeyBuffer().size() >= 2
			&& KEY_M->getKeyBuffer(0) == 'S'
			&& KEY_M->getKeyBuffer(1) == 'S'
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& _thisPl->getInfo().weaponType == WEAPON_TYPE::NONE)
			_thisPl->setState(PL_STATE::COMBO3);

		//�ð��ȿ� ������ ���� ���� ���
		if (isEndFrame(false)
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc, &(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& ((KEY_M->getVKeyBuffer().size() != 0
				&& KEY_M->getKeyBuffer(0) != 'S') || KEY_M->getVKeyBuffer().size() <= 1)
			)
			_thisPl->setState(PL_STATE::IDLE);
	}

	//�ȱ�
	walkPattern();
	
}

void playerCombo2::ExitState()
{
}
