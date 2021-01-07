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
		������Ʈ�� ���ʹ̸� ��ġ�մϴ�.
	====================================================================*/
	_enemyM->pushEnemy(ENEMY_TYPE::BOSS, vector3(WINSIZEX / 4 + 80, 0, WINSIZEY / 2 + 40));

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
