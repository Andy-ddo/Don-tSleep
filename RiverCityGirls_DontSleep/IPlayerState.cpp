#include "stdafx.h"
#include "IPlayerState.h"
#include "EnemyManager.h"
#include "Enemy.h"

//������Ʈ �Ͻ����� ���� 
bool IPlayerState::pauseUpdate()
{
	//Ű������ �Ұ����ϰ�� 
	if (!_thisPl->getInfo().isControl) return true;

	//�׿�
	else return false;
}

//������ ���࿩��
bool IPlayerState::isEndFrame(bool reverse)
{
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
	{
		//���� �����ӹ�ȣ�� ����ȣ�� ����������� ��
		if (reverse == false && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())
			return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() <= 0)
			return true;

		return false;
	}
	case DIRECTION::RIGHT:
	{
		//���� �����ӹ�ȣ�� 0 ��ȣ�� ����������� ��
		if (reverse == false && _thisPl->getObj().img->getFrameX() <= 0) return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())return true;
		return false;
	}
	}
}

void IPlayerState::walkPattern()
{
	//�ȱ�
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
}

void IPlayerState::basePattern()
{
	//�ȱ�
	walkPattern();

	//����
	if (KEY_M->isStayKeyDown('F'))_thisPl->setState(PL_STATE::GUARD);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO1);

}

//���ݻ��¸� �������� ��ȯ
void IPlayerState::checkAttack()
{
	RECT temp;
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (IntersectRect(&temp, &_thisPl->getInfo().attackInfo._obj.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& _thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj()))
			_thisPl->SetIsAttack(true);
	}
}

//������
void IPlayerState::sAttack()
{
	if (KEY_M->isOnceKeyDownV('D'))
	{
		for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
		{
			//if (_thisPl->getEnemyM()->getVEnemy()[i]);
			_thisPl->setState(PL_STATE::SATTACK);
			//�� �����°� ���������¸� �������� ���۹ٲٱ�
			//if (_thisPl->getEnemyM()->getVEnemy()[i]);
		}
	}
}

//�����̵�
void IPlayerState::lineMove(float speed)
{	
	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -speed, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, speed, 0);
}

//�¿��̵�
void IPlayerState::crossMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-speed, 0, 0);
}
