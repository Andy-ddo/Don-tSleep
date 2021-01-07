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
	vector<tagWall> _vBackWall;
	vector<tagWall> _vLeftWall;
	vector<tagWall> _vRightWall;
	tagWall _floor;

	float _zAngle;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void backWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void leftWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void rightWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void floorInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);

	/*====================================================================
									GETTER
	====================================================================*/
	EnemyManager* getEnemyM() { return _enemyM; }
	ObjectManager* getObjectM() { return _objectM; }
	vector<tagWall> getLeftWall() { return _vLeftWall; }
	vector<tagWall> getBackWall() { return _vBackWall; }
	vector<tagWall> getRightWall() { return _vRightWall; }
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

