#include "stdafx.h"
#include "playerGrab.h"

void playerGrab::EnterState()
{
	//���̶� ���ͼ�Ʈ��Ʈ�ϰ� / ���� GRAB�����ϰ��

	//Ÿ�̸��ʱ�ȭ
	_stateTimer = TIME_M->getWorldTime();
	//�̹�������
	_thisPl->changeImg("pl_grab", false);
	_thisPl->setIsControl(false);
}

void playerGrab::UpdateState()
{
	if (KEY_M->isOnceKeyDownV('Q'))
	{
		_thisPl->changeImg("pl_grab", false);
	}

}

void playerGrab::ExitState()
{
}
