#pragma once
#include "Scene.h"

/*====================================================================
	���� ���Դϴ�. ���� �Ŀ��� Ÿ��Ʋ ������ ���ư� �� �ֽ��ϴ�.
====================================================================*/

class EndingScene : public Scene
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
