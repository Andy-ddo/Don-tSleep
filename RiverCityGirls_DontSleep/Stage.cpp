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
	_enemyM->update();
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
	wallRender();
}

void Stage::polylineRender(vector3 A, vector3 B)
{
	POINT temp[2];
	temp[0] = PointMake(A.x, A.z);
	temp[1] = PointMake(B.x, B.z);
	Polyline(getMapDC(), temp, 2);
}

void Stage::wallRender()
{
	if (KEY_M->isToggleKey(VK_TAB))
	{
		polylineRender(_leftWall.LT, _leftWall.RT);
		polylineRender(_leftWall.RT, _leftWall.RB);
		polylineRender(_leftWall.RB, _leftWall.LB);
		polylineRender(_leftWall.LB, _leftWall.LT);

		polylineRender(_backWall.LT, _backWall.RT);
		polylineRender(_backWall.RT, _backWall.RB);
		polylineRender(_backWall.RB, _backWall.LB);
		polylineRender(_backWall.LB, _backWall.LT);

		polylineRender(_rightWall.LT, _rightWall.RT);
		polylineRender(_rightWall.RT, _rightWall.RB);
		polylineRender(_rightWall.RB, _rightWall.LB);
		polylineRender(_rightWall.LB, _rightWall.LT);

		polylineRender(_floor.LB, _floor.RB);
	}	
}
