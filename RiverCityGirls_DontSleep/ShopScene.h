#pragma once
#include "Scene.h"
/*====================================================================
	���� ���Դϴ�. ���� ���� �����Ͱ� �����Ǿ�� �ϹǷ� Data Manager�� �̿��մϴ�.
====================================================================*/
class ShopScene : public Scene
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

