#include "stdafx.h"
#include "GameScene.h"

#include "StageManager.h"
#include "CollisionManager.h"
#include "Player.h"

HRESULT GameScene::init()
{
	UI_M->addDoor("doorLeft", IMG_M->findImage("UI_UnLocked_Door"), vector3(0, 0, 0), 155);
	UI_M->addDoor("doorRight", IMG_M->findImage("UI_UnLocked_Door"), vector3(0, 0, 0), 155);
	/*====================================================================
		���� ���� �������� �Ŵ����� �ݸ��� �Ŵ����� �����ϴ�.
	====================================================================*/
	_colM = new CollisionManager;
	_colM->init();

	_stageM = new StageManager;
	_stageM->init();

	_colM->setLinkStageM(_stageM);
	_colM->setLinkPlayer(_stageM->getPlayer());
	_stageM->getPlayer()->setLinkColM(_colM);
	_stageM->setLinkColM(_colM);

	/*====================================================================
		UI�� �̹����� �߰��մϴ�.
	====================================================================*/
	//���� �� �̹���
	UI_M->setIsActive(true);
	UI_M->addImage("UI_kyoko", IMG_M->findImage("UI_kyoko"), vector3(70, 80, 0));
	UI_M->findUI("UI_kyoko")->setActive(true);

	//���� HP�� (�ӽ�)
	UI_M->addBar("bossHPBar", IMG_M->findImage("bossHPFront"), IMG_M->findImage("bossHPBack"), vector3(200, 580, 0),
		&_stageM->getPlayer()->getInfo().hp, &_stageM->getPlayer()->getInfo().maxHP);
	UI_M->findUI("bossHPBar")->setActive(true);

	return S_OK;
}

void GameScene::release()
{
	_stageM->release();
	SAFE_DELETE(_stageM);
}

void GameScene::update()
{
	_stageM->update();

}

void GameScene::render()
{
	/*====================================================================
		�������� �Ŵ����� ���� ��Ű��, Z-Order�� ���� ������ �����մϴ�.
	====================================================================*/
	_stageM->render();
	ZORDER_M->render();
}
