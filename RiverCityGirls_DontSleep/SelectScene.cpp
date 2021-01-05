#include "stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init()
{
	/*====================================================================
		���� ������ ���̺� ������ �ε��� �� �ְ� �մϴ�.
	====================================================================*/

	/*====================================================================
		���� ����� �����ϰ�, Ÿ��Ʋ�� UI�� ����ϸ�, ����� ������ŵ�ϴ�.
	====================================================================*/
	backGround = IMG_M->findImage("select_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);

	/*====================================================================
		�� ĳ���� �̹����� ���� �������� �̵���ŵ�ϴ�.
	====================================================================*/
	_illust = IMG_M->findImage("select_illust");
	_illustPos = vector3(350.0f, WINSIZEY / 2 + 400.0f, 0.0f);
	_illustInter = new Interpolation;
	_illustInter->moveTo(&_illustPos, 450, WINSIZEY / 2 + 400, 0.2f);
	_ratioOffset = 0.0f;

	/*====================================================================
		UI�� ���� �̹����� �߰��ϰ�, ������ �� �ֵ��� �մϴ�.
	====================================================================*/


	/*====================================================================
		ī�޶� �����Ӱ� ��� �̺�Ʈ�� �����մϴ�.
	====================================================================*/
	EVENT_M->addEvent(new waitForSec(0.3f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.1f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.8, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	return S_OK;
}

void SelectScene::release()
{
}

void SelectScene::update()
{
	_illustInter->update();

	//RND->getInt(2) == 0 ? _ratioOffset = 0.0f : _ratioOffset = 0.05f;

	/*====================================================================
		ī�޶�� �߾ӿ� ������Ű��, ���͸� ġ�� ���� ������ �ѱ�ϴ�.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);
	if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)) && !EVENT_M->isEvent())
	{
		SCENE_M->changeScene("loading");			//�ε� ������ ����
	}

}

void SelectScene::render()
{
	/*====================================================================
		����� loop ���� ���� ���� �����ϰ�, ĳ���� �̹����� ��� �ݴϴ�
	====================================================================*/
	backGround->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
	IMG_M->findImage("start_frame")->render(getMapDC(), 800, 450, 1280 / 1600.0f , 720 / 900.0f);
	_illust->render(getMapDC(), _illustPos.x, _illustPos.y, 0.7f + _ratioOffset, 0.7f + _ratioOffset);
}
