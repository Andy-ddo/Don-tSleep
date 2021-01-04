#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	/*====================================================================
		Ÿ��Ʋ ������ ��Ʈ�� ���� ������ �����մϴ�.
	====================================================================*/

	/*====================================================================
		���� ����� �����ϰ�, ���� Ÿ��Ʋ UI�� �����մϴ�.
		Ÿ��Ʋ�� UI�� ����ϸ�, ����� ������ŵ�ϴ�.
	====================================================================*/
	backGround = IMG_M->findImage("start_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);

	/*====================================================================
		��Ʈ�� ���� �̺�Ʈ�� �����մϴ�. ���� ���� ������ ��� ������Ʈ�� ������ ����ϴ�.
	====================================================================*/
	EVENT_M->addEvent(new moviePlay(VIDEOTYPE::GAME_INTRO));

	/*====================================================================
		UI�� Ÿ��Ʋ �̹����� �߰��ϰ�, UI �̵��� �����ŵ�ϴ�.
	====================================================================*/
	_title = IMG_M->findImage("start_title");
	UI_M->setIsActive(true);
	UI_M->addImage("title", _title, { vector3(WINSIZEX / 2, WINSIZEY / 2,0) });
	UI_M->findUI("title")->setActive(true);
	UI_M->findUI("title")->move(vector3(WINSIZEX / 2 - 200, WINSIZEY / 2, 0), 3);

	/*====================================================================
		ī�޶� �����Ӱ� ��� �̺�Ʈ�� �����մϴ�.
	====================================================================*/
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.001f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.5, 0.001f));
	EVENT_M->addEvent(new waitForSec(0.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.001f));

	return S_OK;
}

void TitleScene::release()
{

}

void TitleScene::update()
{
	/*====================================================================
		ī�޶�� �߾ӿ� ������Ű��, ���͸� ġ�� Ÿ��Ʋ UI�� ���� ���� ������ �ѱ�ϴ�.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);
	if (KEY_M->isOnceKeyDown(VK_RETURN))
	{
		UI_M->findUI("title")->setActive(false);	//title UI ��Ȱ��ȭ
		UI_M->popUI("title");						//title UI �ƿ� ����
		SCENE_M->changeScene("loading");			//���� ����
	}

	/*====================================================================
		����� x+1, y+1 �밢�� �������� ���� ��ŵ�ϴ�.
	====================================================================*/
	loop.x++; loop.y++;
}

void TitleScene::render()
{
	/*====================================================================
		����� loop ���� ���� ���� �����ϰ�, ĳ���� �̹����� ��� �ݴϴ�
	====================================================================*/
	backGround->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
	IMG_M->findImage("start_kyoko")->render(getMapDC(), WINSIZEX / 2 + 200, WINSIZEY / 2);
}
