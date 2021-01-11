#include "stdafx.h"
#include "playerHit.h"


void playerHit::EnterState()
{
	//�̹û��·� �����
	_thisPl->getInfo().isImmune = true;
	_thisPl->getRefObj().alpha = 180;

	//�̹�������
	_thisPl->changeImg("pl_hit", false);

	//Ű���ۺҰ�
	_thisPl->setIsControl(false);

	//������ ����
	_thisPl->getInfo().hitCount++;

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
