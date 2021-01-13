#pragma once
#include "gameNode.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#define BGMVOLUME .5f
#define SFXVOLUME .5f

class StageManager;
/*====================================================================
	��� ���������� ���ʹ� �Ŵ����� ������Ʈ �Ŵ����� �����ϴ�.
	������ �Ŵ����� ����� ������������ �����Ӱ� ��ġ�� �� �ֵ��� �մϴ�.
====================================================================*/

struct tagWall
{
	bool isUsed;
	vector3 LT, RT, RB, LB;
	tagWall()
	{
		isUsed = false;
	}
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
	tagWall _pool;
	tagWall _leftDoor;
	tagWall _rightDoor;

	float _zAngle;

	bool eventEnd;

	
	DOOR_ACTIVITY _doorActive;
	int _enemyCount;
	int _maxEnemyCount;
	float _keyTimer;

	bool activeDoor;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void backWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void leftWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void rightWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void floorInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void poolInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	/*====================================================================
									GETTER
	====================================================================*/
	EnemyManager* getEnemyM() { return _enemyM; }
	ObjectManager* getObjectM() { return _objectM; }
	vector<tagWall> getLeftWall() { return _vLeftWall; }
	vector<tagWall> getBackWall() { return _vBackWall; }
	vector<tagWall> getRightWall() { return _vRightWall; }
	tagWall getFloor() { return _floor; }
	tagWall getPool() { return _pool; }
	tagWall getLeftDoor() { return _leftDoor; }
	tagWall getRightDoor() { return _rightDoor; }
	DOOR_ACTIVITY getDoorActive() { return _doorActive; }
	int getEnemyCount() { return _enemyCount; }
	int getMaxEnemyCount() { return _maxEnemyCount; }
	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setEnemyCount(int num) { _enemyCount = num; }

	/*====================================================================
									����׿� �ӽ��Լ�
	====================================================================*/
	void polylineRender(vector3 A, vector3 B);
	void wallRender();

};

