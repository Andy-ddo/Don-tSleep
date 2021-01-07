#include "stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init()
{
	Stage::init();

	/*====================================================================
		���������� ��� �̹����� �����ϰ�, ī�޶󿡰� �� ����� �˷� �ݴϴ�.
	====================================================================*/
	backGround = IMG_M->findImage("bossStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		���������� ���� ��ġ�մϴ�. LT, RT, RB, LB ��!!
	====================================================================*/
	backWallInit(vector3(430, WINSIZEY, 0), vector3(1655, WINSIZEY, 0), vector3(1655, 0, 355), vector3(430, 0, 355));

	leftWallInit(vector3(0, WINSIZEY, 0), vector3(430, WINSIZEY, 0), vector3(430, 0, 355), vector3(0, 0, 790));

	rightWallInit(vector3(1655, WINSIZEY, 0), vector3(2077, WINSIZEY, 0), vector3(2077, 0, 775), vector3(1655, 0, 355));

	floorInit(vector3(0, 0, 790), vector3(2077, 0, 770), vector3(2077, 0, 810), vector3(0, 0, 810));

	/*====================================================================
		������Ʈ�� ���ʹ̸� ��ġ�մϴ�.
	====================================================================*/
	_enemyM->pushEnemy(ENEMY_TYPE::BOSS, vector3(WINSIZEX , 0, WINSIZEY));

	/*====================================================================
		�������� ���� �� ���� �� �̺�Ʈ�� �߰��մϴ�.
	====================================================================*/
	EVENT_M->addEvent(new moviePlay(VIDEOTYPE::BOSS_INTRO));

	return S_OK;
}

void BossStage::release()
{
	Stage::release();
}

void BossStage::update()
{
	Stage::update();
}

void BossStage::render()
{
	Stage::render();
}
