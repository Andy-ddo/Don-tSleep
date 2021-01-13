#pragma once
#include "singletonBase.h"
#include <map>
#include "UI.h"

/*====================================================================
	UI�� �ʿ� ��� �����ϴ� UI �Ŵ����Դϴ�.
====================================================================*/
class UIManager : public singletonBase <UIManager>
{
private:
	map<string, UI*> _mUI;					//UI map
	map<string, UI*>::iterator _miUI;		//UI iterator
	bool _isActive;							//��ü UI Ȱ��ȭ ����

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


/*====================================================================
							GETTER
====================================================================*/
	bool getIsActive() { return _isActive; }

/*====================================================================
							SETTER
====================================================================*/
	void setIsActive(bool active) { _isActive = active; }

/*====================================================================
							ADD UI
====================================================================*/
	void addImage(string, image* img, vector3 pos);													//���� �̹��� UI�� �߰��Ѵ�.
	void addBar(string name, image * front, image * back, vector3 pos, int* current, int* max);		//���α׷��� �� UI�� �߰��Ѵ�.
	void addLock(string name, vector3 pos);
/*====================================================================
							FUNCTION
====================================================================*/
	void popUI(string name);		//UI�� �����Ѵ�.

	UI* findUI(string name);		//UI�� ã�´�.

};

