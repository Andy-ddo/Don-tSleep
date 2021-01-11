#include "stdafx.h"
#include "playerHit.h"
#include "EnemyManager.h"
#include "Enemy.h"


void playerHit::EnterState()
{
	RECT temp;

	//�̹û��·� �����
	_thisPl->getInfo().isImmune = true;
	_thisPl->getRefObj().alpha = 180;

	//ü�� ���
	for (int i = 0; i !=_thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		_thisPl->getInfo().hp -= _thisPl->getEnemyM()->getVEnemy()[i]->getInfo().attack;
		//������ ����
		_thisPl->getInfo().hitCount++;
	}

	//�̹�������
	_thisPl->changeImg("pl_hit", false);

	//Ű���ۺҰ�
	_thisPl->setIsControl(false);

	

	//���ⶳ��߸���
	dropWeapon();
}

void playerHit::UpdateState()
{

	//�������� ������ Ű���� ���
	if (isEndFrame(false))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerHit::ExitState()
{
}
