#include "stdafx.h"
#include "Stage.h"
#include "ObjectManager.h"

/*====================================================================
	�������� �ʱ�ȭ �� ���ʹ� �Ŵ����� ������Ʈ �Ŵ����� �Ҵ��ϰ� �ʱ�ȭ�մϴ�.
====================================================================*/
HRESULT Stage::init()
{
	_enemyM = new EnemyManager;
	_enemyM->init();
	_enemyM->setLinkStageM(_stageM);

	_objectM = new ObjectManager;
	_objectM->init();
	return S_OK;
}

void Stage::release()
{
	_enemyM->release();
	SAFE_DELETE(_enemyM);

	_objectM->release();
	SAFE_DELETE(_objectM);
}

void Stage::update()
{
	//_enemyM->update();
	_objectM->update();

}

void Stage::render()
{
	/*====================================================================
		���� ���ʹ̿� ������Ʈ�� �����Ѵ�.
	====================================================================*/
	backGround->render(getMapDC(), backGround->getWidth() / 2, backGround->getHeight() / 2);
	_enemyM->render();
	_objectM->render();
}
