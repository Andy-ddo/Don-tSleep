#pragma once
#include "singletonBase.h"
#include <map>
#include "UI.h"

/*====================================================================
	UI를 맵에 담아 관리하는 UI 매니저입니다.
====================================================================*/
class UIManager : public singletonBase <UIManager>
{
private:
	map<string, UI*> _mUI;					//UI map
	map<string, UI*>::iterator _miUI;		//UI iterator
	bool _isActive;							//전체 UI 활성화 여부

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
	void addImage(string, image* img, vector3 pos);													//단일 이미지 UI를 추가한다.
	void addBar(string name, image* front, image * back, vector3 pos, int* current, int* max);		//프로그레스 바 UI를 추가한다.
	void addDoor(string name, image* img, vector3 pos, int alpha);									//문 UI를 추가한다.
/*====================================================================
							FUNCTION
====================================================================*/
	void popUI(string name);		//UI를 제거한다.

	UI* findUI(string name);		//UI를 찾는다.

};

