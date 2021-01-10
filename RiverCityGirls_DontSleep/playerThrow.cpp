#include "stdafx.h"
#include "playerThrow.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerThrow::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_wBatThrow", false);

	//���� Ʈ���� ����
	_thisPl->getInfo().isThrow = true;

	_isCollision = false;

	_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
	_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
	_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;

	_thisPl->getInfo().attackObj->isRender = true;
}

void playerThrow::UpdateState()
{
	//���� ��Ʈ�� ���� ������Ʈ�� ��ġ�� ����.
	_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getInfo().attackObj->pos.x,
		_thisPl->getInfo().attackObj->pos.z + _thisPl->getInfo().attackObj->pos.y,
		_thisPl->getInfo().attackObj->size.x + 200, _thisPl->getInfo().attackObj->size.z + 100);

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
	if (isEndFrame(false))
	{
		//���������Ҿ����
		//dropWeapon();

		//Ű���� ������ ���·� ����
		_thisPl->setIsControl(true);

		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerThrow::ExitState()
{
}
