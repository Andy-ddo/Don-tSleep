#include "stdafx.h"
#include "EasyStage.h"

HRESULT EasyStage::init()
{
	Stage::init();

	/*====================================================================
		���������� ��� �̹����� �����ϰ�, ī�޶󿡰� �� ����� �˷� �ݴϴ�.
	====================================================================*/
	backGround = IMG_M->findImage("easyStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		������Ʈ�� ���ʹ̸� ��ġ�մϴ�.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(WINSIZEX - 300, 0, WINSIZEY / 2));
	_objectM->pushItem(ITEM_TYPE::MEAT, vector3(WINSIZEX / 3 * 2, 0, WINSIZEY / 2));

	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 4 + 80, 0, WINSIZEY / 2 + 40));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 4 + 80, 0, WINSIZEY / 2 - 100));

	/*====================================================================
		�������� ���� �� ���� �� �̺�Ʈ�� �߰��մϴ�.
	====================================================================*/
	//�̺�Ʈ�� ���� �׽�Ʈ ������ �ƹ��ų� �־� ����! �ǰ��ϸ� ��� ����ų� �ּ�ó�� �ϼ���.
	/*
	EVENT_M->addEvent(new cameraMove(vector3(500, 0, 0), 8, 1.0, 0.1f));
	EVENT_M->addEvent(new waitForSec(0.3f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 100, 0), 8, 1.2, 0.01f));
	EVENT_M->addEvent(new waitForSec(0.5f));
	EVENT_M->addEvent(new cameraMove(vector3(600, 100, 0), 8, 1.0, 0.1f));
	EVENT_M->addEvent(new cameraMove(vector3(10, 10, 0), 8, 1.0, 0.1f));*/
	
	return S_OK;
}

void EasyStage::release()
{
	Stage::release();

}

void EasyStage::update()
{
	Stage::update();
}

void EasyStage::render()
{
	Stage::render();
}
