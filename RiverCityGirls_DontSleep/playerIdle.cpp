#include "stdafx.h"
#include "playerIdle.h"

void playerIdle::EnterState()
{
	_thisPl->changeImg("pl_idle",true);
	//Ű���� ������ ���·� ����
	_thisPl->setIsControl(true);
	//���������� ������ ���·� ����
	_thisPl->setIsConDest(true);

	//Ÿ�̸Ӹ� ����Ÿ�̸ӷ� ���缭 �ʱ�ȭ
	_stateTimer = TIME_M->getWorldTime();
	
}

void playerIdle::UpdateState()
{
	//�����ð����� �������� ������ ��ٸ� ���·� ��ȯ
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)_thisPl->setState(PL_STATE::WAIT);
	//������Ʈ ���� ����
	if (pauseUpdate())return;

	//�⺻ ����
	basePattern();
	
	//������
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);
}

void playerIdle::ExitState()
{
}
