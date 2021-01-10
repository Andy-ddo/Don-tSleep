#include "stdafx.h"
#include "playerCombo3.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo3::EnterState()
{
	_thisPl->changeImg("pl_comboAttack3", false);
	_isCollision = false;

	//���ݿ���
	checkAttack();
}

void playerCombo3::UpdateState()
{
	_thisPl->SetIsAttack(false);

	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
	
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
	//������ ù�浹��
	if (!_isCollision
		&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
	{
		_isCollision = true;
	}
	}

	//�ȱ�
	walkPattern();
}

void playerCombo3::ExitState()
{
}
