#pragma once
#include "Scene.h"

/*====================================================================
	Ÿ��Ʋ ���Դϴ�. �̰����� Ÿ��Ʋ ����, ���� â, �ɼ� ���� �����մϴ�.
====================================================================*/
class TitleScene : public Scene
{
private:
	vector3 loop;
	image* _title;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

