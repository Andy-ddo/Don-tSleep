#pragma once
#include "gameNode.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

class StageManager;
/*====================================================================
	��� ���������� ���ʹ� �Ŵ����� ������Ʈ �Ŵ����� �����ϴ�.
	������ �Ŵ����� ����� ������������ �����Ӱ� ��ġ�� �� �ֵ��� �մϴ�.
====================================================================*/
class Stage : public gameNode
{
protected:
	EnemyManager* _enemyM;
	ObjectManager* _objectM;
	StageManager* _stageM;

	image* backGround;

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


	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }

};

