#pragma once
#include "gameNode.h"
#include "Object.h"

/*====================================================================
	������Ʈ �Ŵ����Դϴ�. ������Ʈ�� ���Ϳ� �־� �����ϸ�,
	push�� ������Ʈ�� ���� ���� �� �ֽ��ϴ�.
====================================================================*/
class ObjectManager : public gameNode
{
private:
	vector<Object*> _vObject;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

/*====================================================================
								GETTER
====================================================================*/
	vector<Object*> getVObject() { return _vObject; }

/*====================================================================
								FUNCTION
====================================================================*/
	void pushObject(OBJECT_TYPE type, vector3 pos);		//������Ʈ�� �ִ´�.
	void pushItem(ITEM_TYPE type, vector3 pos);			//�������� �ִ´�.
	void pushWeapon(WEAPON_TYPE type, vector3 pos);		//���⸦ �ִ´�.

	void popObject(int index);						//������Ʈ�� �����Ѵ�.
};

