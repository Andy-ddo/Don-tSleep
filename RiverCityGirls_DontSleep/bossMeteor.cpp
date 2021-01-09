#include "stdafx.h"
#include "bossMeteor.h"
#include "Boss.h"
#include "Player.h"

void bossMeteor::EnterState()
{
	_angle = PI / 2;
	_speed = 8.0f;
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_meteor");

	if (_thisBs->getdest() == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}

	else if (_thisBs->getdest() == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void bossMeteor::UpdateState()
{
	

	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 10.0f)
	{
		_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
			_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
		_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;

		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z, 100, 100);
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) 충돌처리 필요, 플레이어 렉트? 
		// 화면위로 올려서 그래비티를 받게 해서 바닥만 충돌을 일으키거나, 
		// 이미지 처리로 충돌...(?)
		// 지속 처리 필요, 좌표 처리(?)
	}
}

void bossMeteor::ExitState()
{
	_thisBs->getInfo().isAttack = false;
}
