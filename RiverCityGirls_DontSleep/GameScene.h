#pragma once
#include "Scene.h"

class StageManager;

/*====================================================================
	���� ���Դϴ�. ���� ���� StageManager�� �����ϴ�.
====================================================================*/

class GameScene : public Scene
{
private:
	StageManager* _stageM;

public:
	GameScene() {}
	~GameScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};