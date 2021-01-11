#include "stdafx.h"
#include "IEnemyState.h"

void IEnemyState::Jump()
{
	//�÷��̾ ������ ���� �ְ� ������ �ƴϸ� ������ �Ѵ�.
	if (_thisEn->getPlayerAddress()->getObj().pos.y < _thisEn->getObj()->pos.y && !_thisEn->getPlayerAddress()->getInfo().isSky)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_JUMP);
		}
	}
}

void IEnemyState::LookAtPlayer()
{

	//�÷��̾ �����ʿ� ������ ������ ������ ����. �ݴ�� ������ ����.
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::RIGHT;
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::LEFT;
}

void IEnemyState::Attack()
{
	//���� ��Ʈ ũ��� ��ġ ����
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 100, 200);
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left - 100, _thisEn->getObj()->rc.top, 100, 200);
	}
	_thisEn->getInfo().isAttack = true;
}

bool IEnemyState::endFrame()
{
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x >= _thisEn->getObj()->img->getMaxFrameX())
	{
		return true;
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x <= 0)
	{
		return true;
	}
	return false;
}
