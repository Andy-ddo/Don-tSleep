#include "stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init()
{
	/*====================================================================
		���� ī�޶��� �� ����� �����Ѵ�.
	====================================================================*/
	backGround = IMG_M->findImage("load_background");
	CAMERA_M->SetMap(*this, backGround);


	/*====================================================================
		UI �ε� �ٸ� ȣ���Ѵ�.
	====================================================================*/
	_max = 100;
	_count = 0;

	UI_M->setIsActive(true);
	UI_M->addBar("loadingBar", IMG_M->findImage("bossHPFront"), IMG_M->findImage("bossHPBack"), vector3(200, 600, 0), &_count, &_max);
	UI_M->findUI("loadingBar")->setActive(true);

	/*====================================================================
		��������Ʈ �̹����� �ִϸ��̼��� �����Ѵ�.
		//�̰� �ִϸ��̼� ��� ����ü �� �ȵ����ФФ��� ���� �� �߸��ϰ� �ִ� �ǰ�...?
	====================================================================*/
	_sprite = IMG_M->findImage("loading_sprite");
	_ani = new animation;
	_ani->init(_sprite->getWidth(), _sprite->getHeight(), _sprite->getFrameWidth(), _sprite->getFrameHeight());
	_ani->setDefPlayFrame(true, true);
	_ani->setFPS(1);
	_ani->start();

	/*====================================================================
		�̱� �����带 ����Ѵ�.
	====================================================================*/
	CreateThread(
		NULL,				//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,				//�������� ����ũ��(NULL�� �θ� ���ξ����� ũ��� ����)
		threadFunction,		//������ ����� �Լ� ��
		this,				//������ �Ű�����(this�� �θ� �� Ŭ����)
		NULL,				//�������� Ư��(��ٸ���, �ٷ� ����(NULL�̸� ��� �ش�))
		NULL				//������ ���� �� �������� ID �Ѱ��� ������ NULL�� �д�
	);
	
	return S_OK;
}

void LoadingScene::release()
{
}

void LoadingScene::update()
{
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	//�ε��� �� �Ǹ�
	if (_count == _max)
	{
		UI_M->findUI("loadingBar")->setActive(false);
		SCENE_M->changeScene("title");
	}
}

void LoadingScene::render()
{
	backGround->render(getMapDC());
	_sprite->aniRender(getMapDC(), WINSIZEX - 150, WINSIZEY - 220, _ani);
	//_sprite->frameRender(getMapDC(), WINSIZEX - 200, WINSIZEY - 200, 1, 0);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	LoadingScene* helper = (LoadingScene*)lpParameter;

	while (helper->_count!=helper->_max)
	{
		Sleep(1);
		++helper->_count;
	}

	return 0;
}