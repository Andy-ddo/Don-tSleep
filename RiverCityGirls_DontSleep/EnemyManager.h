#pragma once
#include "gameNode.h"

class Enemy;

/*====================================================================
	���ʹ� �Ŵ����Դϴ�. ���ʹ̸� ���Ϳ� �־� �����ϸ�,
	push�� ���ʹ̸� ���� ���� �� �ֽ��ϴ�.
====================================================================*/

class EnemyManager : public gameNode
{
private:
	vector<Enemy*> _vEnemy;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pushEnemy(ENEMY_TYPE type, vector3 pos);
};

