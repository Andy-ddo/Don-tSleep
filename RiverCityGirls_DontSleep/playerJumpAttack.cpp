#include "stdafx.h"
#include "playerJumpAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerJumpAttack::EnterState()
{
	//���� ���� �Ұ�
	_thisPl->setIsConDest(false);

	_thisPl->changeImg("pl_jumpAttack",false);

	//����Ÿ���� �������� ����
	if (_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)_thisPl->setWeaponType(WEAPON_TYPE::NONE);
	_isCollsion = false;
}

void playerJumpAttack::UpdateState()
{
	//���� ����
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (!_isCollsion
			&&_thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj(), 30)
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{

			if (!_thisPl->getInfo().isAttack)
			{
				_thisPl->SetIsAttack(true);
				_isCollsion = true;
			}
		}
	}

	
	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed / 2);

}

void playerJumpAttack::ExitState()
{
}
