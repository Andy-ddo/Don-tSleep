#include "stdafx.h"
#include "Event.h"
#include "Video.h"
#include "Player.h"

/*====================================================================
	ī�޶� �̵��� ���� ���� �̺�Ʈ
====================================================================*/
cameraMove::cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed)
{
	_goal = goal;

	_goal.x += WINSIZEX / 2;
	_goal.y += WINSIZEY / 2;
	 
	_moveSpeed = moveSpeed;
	_mag = mag;
	_magSpeed = magSpeed;
}
void cameraMove::enter()
{
	Event::enter();
	if(_player) _player->setIsControl(false);
}

bool cameraMove::update()
{
	CAMERA_M->SetPos(_goal.x, _goal.y, 0, 0, _moveSpeed);
	CAMERA_M->SetMagnification(_mag, _magSpeed);

	if (getDistance(CAMERA_M->GetX(), CAMERA_M->GetY(), _goal.x, _goal.y) < 10)
	{
		CAMERA_M->SetPos(_goal.x, _goal.y);
		return true;
	}
	return false;
}

void cameraMove::exit()
{
	if (_player) _player->setIsControl(true);

}

/*====================================================================
	������ ��� �̺�Ʈ
====================================================================*/
moviePlay::moviePlay(VIDEOTYPE file)
{
	_video = new Video;
	switch (file)
	{
		case VIDEOTYPE::GAME_INTRO:
			_video->init("source/video/intro.wmv");
		break;

		case VIDEOTYPE::BOSS_INTRO:
			_video->init("source/video/boss.wmv");
		break;

		default:
		break;
	}
}

void moviePlay::enter()
{
	Event::enter();

	_video->play();
	_isMovie = true;
}

bool moviePlay::update()
{
	//���ͷ� ��ŵ
	if (_video->getIsPlaying() && (KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE))) _video->stop();

	//���� ����� �������� Ȯ��
	if (_video->getIsPlaying())
	{
		char lp[10];
		long mode = MCIWndGetMode(_video->getVideo(), lp, sizeof(lp));
		if (mode == 525)  _video->stop();	//���� ����� �����Ŵ
	}
	//���� ����� ������ ����
	if (!_video->getIsPlaying()) return true;

	return false;
}

void moviePlay::exit()
{
	//���� ������� �ƴ϶�� ��.
	_isMovie = false;

	//���� ����
	SAFE_DELETE(_video);
}

/*====================================================================
	���â�� ��ȭ �̺�Ʈ
====================================================================*/
void dialogue::enter()
{
	Event::enter();

}

bool dialogue::update()
{
	return true;

}

void dialogue::exit()
{
}

/*====================================================================
	second�� ����ϴ� �̺�Ʈ
====================================================================*/
waitForSec::waitForSec(float sec)
{
	_sec = sec;
}

void waitForSec::enter()
{
	Event::enter();
	if (_player) _player->setIsControl(false);

	_endTime = TIME_M->getWorldTime() + _sec;
}

bool waitForSec::update()
{
	if (TIME_M->getWorldTime() >= _endTime) return true;
	return false;
}

void waitForSec::exit()
{
	if (_player) _player->setIsControl(true);
}
