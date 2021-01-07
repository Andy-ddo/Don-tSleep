#include "stdafx.h"
#include "playerCombo2.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo2::EnterState()
{
	_thisPl->changeImg("pl_comboAttack2", false);
}

void playerCombo2::UpdateState()
{
	//������ ù�浹��
	if (!_thisPl->getInfo().isAttack
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc)))
	{
		_thisPl->SetIsAttack(true);
	}

	//����Ű�Է� �޾Ƽ� ���Ϳ� ����
	if (KEY_M->isOnceKeyDownV('S'));
	cout << KEY_M->getVKeyBuffer().size() << endl;

	//������ 2�޺� ������ ���
	if (isEndFrame(false)
		&& KEY_M->getVKeyBuffer().size() != 0
		&& KEY_M->getKeyBuffer(0) == 'S'
		&& KEY_M->getKeyBuffer(1) == 'S'
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc))
		&& _thisPl->getInfo().weaponType == WEAPON_TYPE::NONE
		)
		_thisPl->setState(PL_STATE::COMBO3);

	//�ð��ȿ� ������ ���� ���� ���
	if (isEndFrame(false)
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc, &(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc))
		&& ((KEY_M->getVKeyBuffer().size() != 0
			&& KEY_M->getKeyBuffer(0) != 'S') || KEY_M->getVKeyBuffer().size() == 0)
		)
		_thisPl->setState(PL_STATE::IDLE);

	//�ȱ�
	walkPattern();
	
}

void playerCombo2::ExitState()
{
}
