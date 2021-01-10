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
		���������� ���� ��ġ�մϴ�. LT, RT, RB, LB ��!!
	====================================================================*/
	backWallInit(vector3(350, WINSIZEY, 0), vector3(1635, WINSIZEY, 0), vector3(1635, 0, 385), vector3(350, 0, 385));

	leftWallInit(vector3(57, WINSIZEY, 0), vector3(350, WINSIZEY, 0), vector3(350, 0, 385), vector3(57, 0, 678));

	rightWallInit(vector3(1635, WINSIZEY, 0), vector3(1928, WINSIZEY, 0), vector3(1928, 0, 678), vector3(1635, 0, 385));

	floorInit(vector3(0, 0, 650), vector3(2028, 0, 650), vector3(1928, 0, 650), vector3(57, 0, 650));

	/*====================================================================
		������Ʈ�� ���ʹ̸� ��ġ�մϴ�.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(440, 0, 545));
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(690, 0, 545));
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(950, 0, 545));
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(1210, 0, 545));
	_objectM->pushItem(ITEM_TYPE::MEAT, vector3(WINSIZEX / 3 * 2, 0, WINSIZEY / 2));


	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 40));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 2 + 100, 0, WINSIZEY / 2 + 40));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLBOY, vector3(WINSIZEX / 2 + 200, 0, WINSIZEY / 2 + 40));


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
	EVENT_M->addEvent(new dialogue(DIALOGLIST::EASY_START), false);

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
