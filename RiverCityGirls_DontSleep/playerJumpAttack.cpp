#include "stdafx.h"
#include "playerJumpAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerJumpAttack::EnterState()
{
	//���� ���� �Ұ�
	_thisPl->getInfo().isConDest = false;

	_thisPl->changeImg("pl_jumpAttack",false);

	//���⸦ ����߸�.
	dropWeapon();

	_isCollision = false;
}

void playerJumpAttack::UpdateState()
{
	RECT _temp;
	//���� ����
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (!_isCollision
			&&_thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj(), 30)
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackObj->rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{

			if (!_thisPl->getInfo().isAttack)
			{
				_thisPl->getInfo().isAttack = true;
				_isCollision = true;
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
