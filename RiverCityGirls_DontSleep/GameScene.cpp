#include "stdafx.h"
#include "GameScene.h"

#include "StageManager.h"
#include "CollisionManager.h"
#include "Player.h"

HRESULT GameScene::init()
{
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
