#pragma once
#include "gameNode.h"

/*====================================================================
	��� ������ ���� ��ӹ޽��ϴ�.
====================================================================*/

class Scene : public gameNode
{
protected:
	image* backGround;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

