#include "stdafx.h"
#include "Event.h"
#include "Video.h"
#include "Player.h"

/*====================================================================
	ī�޶� �̵��� ���� ���� �̺�Ʈ
====================================================================*/
cameraMove::cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed)
{
	_isCameraMove = true;

	_goal = goal;

	_goal.x += WINSIZEX / 2;
	_goal.y += WINSIZEY / 2;

	_moveSpeed = moveSpeed;
	_mag = mag;
	_magSpeed = magSpeed;
}
void cameraMove::enter(bool playerControl)
{
	Event::enter(playerControl);
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
	Event::exit();
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

void moviePlay::enter(bool playerControl)
{
	Event::enter(playerControl);

	_video->play();
	_isMovie = true;
}

bool moviePlay::update()
{
	//���ͳ� �����̽��ٷ� ��ŵ
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
	Event::exit();

	//���� ������� �ƴ϶�� ��.
	_isMovie = false;

	//���� ����
	SAFE_DELETE(_video);
}

/*====================================================================
	���â�� ��ȭ �̺�Ʈ
====================================================================*/

dialogue::dialogue(DIALOGLIST file)
{
	string filePath = "source/dialog/";
	string fileName;
	{
		switch (file)
		{
		case DIALOGLIST::EASY_START:
			fileName = filePath + "easy_start.txt";
			break;
		case DIALOGLIST::BOSS_START:
			fileName = filePath + "boss_start.txt";
			break;
		case DIALOGLIST::BOSS_END:
			fileName = filePath + "boss_end.txt";
			break;
		default:
			break;
		}
	}
	_vScript = TXTDATA->txtLoad(fileName.c_str());
}

void dialogue::enter(bool playerControl)
{
	Event::enter(playerControl);
	if (_player) _player->setIsControl(false);

	_txtIndex = 0;
	_scriptIndex = 0;
}

bool dialogue::update()
{
	_txt = _vScript[_scriptIndex];

	if (_scriptIndex % 2 == 0) _txt = _vScript[++_scriptIndex];
	
	if (_txtIndex <= _txt.length()) _txtIndex++;

	else if (_txtIndex >= _txt.length() && KEY_M->isOnceKeyDown(VK_SPACE))
	{
		_scriptIndex++;
		_txtIndex = 0;
	}

	if (_txtIndex < _txt.length() && KEY_M->isOnceKeyDown(VK_SPACE)) _txtIndex = _txt.length();

	if (_scriptIndex >= _vScript.size()) return true;

	return false;
}

void dialogue::exit()
{
	Event::exit();

}

void dialogue::render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	HFONT font, oldFont;
	RECT rcText = RectMake(200, WINSIZEY - 100, WINSIZEX - 200, 80);
	font = CreateFont(35, 0, 0, 0, 400, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("���"));

	oldFont = (HFONT)SelectObject(hdc, font);
	DrawText(hdc, TEXT(_txt.c_str()), _txtIndex, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);

	DeleteObject(font);
}

/*====================================================================
	second�� ����ϴ� �̺�Ʈ
====================================================================*/
waitForSec::waitForSec(float sec)
{
	_isCameraMove = true;

	_sec = sec;
}

void waitForSec::enter(bool playerControl)
{
	Event::enter(playerControl);
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
	Event::exit();
}

void Event::enter(bool playerControl)
{
	_isEnd = _isMovie = _isCameraMove = false;
	_player->setIsConDest(playerControl);
}

void Event::exit()
{
	_player->setIsControl(true);
}
