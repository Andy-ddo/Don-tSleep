#include "stdafx.h"
#include "GameScene.h"

#include "StageManager.h"
#include "CollisionManager.h"
#include "Player.h"

HRESULT GameScene::init()
{
	UI_M->addLock("LocationLock", vector3(WINSIZEX / 2, 0, WINSIZEY / 2));
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
	UI_M->addImage("UI_kyoko", IMG_M->findImage("UI_kyoko"), vector3(20, 20, 0));
	UI_M->findUI("UI_kyoko")->setActive(true);

	//���� HP��

	DATA_M->setLinkStageM(_stageM);
	DATA_M->setLinkPlayer(_stageM->getPlayer());
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
