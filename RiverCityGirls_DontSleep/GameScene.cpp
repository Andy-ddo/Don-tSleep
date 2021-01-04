#include "stdafx.h"
#include "GameScene.h"

#include "StageManager.h"


HRESULT GameScene::init()
{
	/*====================================================================
		���� ���� �������� �Ŵ����� �����ϴ�.
	====================================================================*/
	_stageM = new StageManager;
	_stageM->init();

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
