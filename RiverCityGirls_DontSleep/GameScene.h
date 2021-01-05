#pragma once
#include "Scene.h"

class StageManager;
class CollisionManager;

/*====================================================================
	���� ���Դϴ�. ���� ���� StageManager�� �����ϴ�.
====================================================================*/

class GameScene : public Scene
{
private:
	StageManager* _stageM;
	CollisionManager* _colM;
public:
	GameScene() {}
	~GameScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};