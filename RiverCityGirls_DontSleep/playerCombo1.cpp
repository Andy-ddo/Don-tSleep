#include "stdafx.h"
#include "playerCombo1.h"
#include "EnemyManager.h"
#include "Enemy.h"

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
	_isCollision = false;

	//���ݿ���
	checkAttack();

}

void playerCombo1::UpdateState()
{
	_thisPl->SetIsAttack(false);


	if (isEndFrame(false) && _thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)
		_thisPl->setState(PL_STATE::IDLE);

	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		//����� ������ ��� �������� ���� �⺻���·� ���ư���.
		if (isEndFrame(false)
			&& !IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
			_thisPl->setState(PL_STATE::IDLE);

	//������ ù�浹��
	
	if (!_isCollision
		&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
	{
		_isCollision = true;
		KEY_M->clearVKey();
	}
	

	//������ ������ ���
	
	if (isEndFrame(false)
		&& KEY_M->getVKeyBuffer().size() != 0
		&& KEY_M->getKeyBuffer(0) == 'S'
		&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
		&& _thisPl->getInfo().weaponType == WEAPON_TYPE::NONE)
	{
		EFFECT_M->play("ef_attack", 10, 10);
			//_thisPl->getInfo().attackInfo._obj.pos.x, _thisPl->getInfo().attackInfo._obj.pos.y);
		_thisPl->setState(PL_STATE::COMBO2);
	}
	
	//�ð��ȿ� ������ ���� ���� ���
	if (isEndFrame(false)
		&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc, &(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
		&& ((KEY_M->getVKeyBuffer().size() != 0
			&& KEY_M->getKeyBuffer(0) != 'S') || KEY_M->getVKeyBuffer().size() == 0)
		)
		_thisPl->setState(PL_STATE::IDLE);
	}

	//�⺻ ����
	basePattern();
}

void playerCombo1::ExitState()
{
}
