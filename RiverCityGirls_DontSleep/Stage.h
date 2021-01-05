#pragma once
#include "gameNode.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

class StageManager;
/*====================================================================
	��� ���������� ���ʹ� �Ŵ����� ������Ʈ �Ŵ����� �����ϴ�.
	������ �Ŵ����� ����� ������������ �����Ӱ� ��ġ�� �� �ֵ��� �մϴ�.
====================================================================*/

struct tagWall
{
	vector3 LT, RT, RB, LB;
};

class Stage : public gameNode
{
protected:
	EnemyManager* _enemyM;
	ObjectManager* _objectM;
	StageManager* _stageM;

	image* backGround;
	tagWall _leftWall;
	tagWall _backWall;
	tagWall _rightWall;
	tagWall _floor;
	float _zAngle;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	/*====================================================================
									GETTER
	====================================================================*/
	EnemyManager* getEnemyM() { return _enemyM; }
	ObjectManager* getObjectM() { return _objectM; }
	tagWall getLeftWall() { return _leftWall; }
	tagWall getBackWall() { return _backWall; }
	tagWall getRightWall() { return _rightWall; }
	tagWall getFloor() { return _floor; }

	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }

	/*====================================================================
									����׿� �ӽ��Լ�
	====================================================================*/
	void polylineRender(vector3 A, vector3 B);
	void wallRender();

};

