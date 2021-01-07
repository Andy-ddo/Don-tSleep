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
	wallRender();
}

void Stage::backWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	tagWall temp;
	temp.LT = lt;
	temp.RT = rt;
	temp.RB = rb;
	temp.LB = lb;
	_vBackWall.push_back(temp);
}

void Stage::leftWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	tagWall temp;
	temp.LT = lt;
	temp.RT = rt;
	temp.RB = rb;
	temp.LB = lb;
	_vLeftWall.push_back(temp);
}

void Stage::rightWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	tagWall temp;
	temp.LT = lt;
	temp.RT = rt;
	temp.RB = rb;
	temp.LB = lb;
	_vRightWall.push_back(temp);
}

void Stage::floorInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	_floor.LT = lt;
	_floor.RT = rt;
	_floor.RB = rb;
	_floor.LB = lb;
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
		for (int i = 0; i < _vBackWall.size(); ++i)
		{
			polylineRender(_vBackWall[i].LT, _vBackWall[i].RT);
			polylineRender(_vBackWall[i].RT, _vBackWall[i].RB);
			polylineRender(_vBackWall[i].RB, _vBackWall[i].LB);
			polylineRender(_vBackWall[i].LB, _vBackWall[i].LT);
		}

		for (int i = 0; i < _vLeftWall.size(); ++i)
		{
			polylineRender(_vLeftWall[i].LT, _vLeftWall[i].RT);
			polylineRender(_vLeftWall[i].RT, _vLeftWall[i].RB);
			polylineRender(_vLeftWall[i].RB, _vLeftWall[i].LB);
			polylineRender(_vLeftWall[i].LB, _vLeftWall[i].LT);
		}

		for (int i = 0; i < _vRightWall.size(); ++i)
		{
			polylineRender(_vRightWall[i].LT, _vRightWall[i].RT);
			polylineRender(_vRightWall[i].RT, _vRightWall[i].RB);
			polylineRender(_vRightWall[i].RB, _vRightWall[i].LB);
			polylineRender(_vRightWall[i].LB, _vRightWall[i].LT);
		}

		polylineRender(_floor.LB, _floor.RB);
	}	
}
