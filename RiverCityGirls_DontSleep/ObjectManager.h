#pragma once
#include "gameNode.h"
#include "Object.h"
#define PARTICLEMAX 60
/*====================================================================
	오브젝트 매니저입니다. 오브젝트를 벡터에 넣어 관리하며,
	push로 오브젝트를 집어 넣을 수 있습니다.
====================================================================*/
class ObjectManager : public gameNode
{
private:
	vector<Object*> _vObject;

	vector<Object*> _vParticleLeftUp;
	vector<Object*> _vParticleLeftDown;
	vector<Object*> _vParticleRightUp;
	vector<Object*> _vParticleRightDown;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Object* findHardPlatform();
	void particleInit(vector3 pos, OBJECT_TYPE type);
	void particleSwitch(OBJECT_TYPE type);


/*====================================================================
								GETTER
====================================================================*/
	vector<Object*> getVObject() { return _vObject; }

/*====================================================================
								FUNCTION
====================================================================*/
	void pushObject(OBJECT_TYPE type, vector3 pos);		//오브젝트를 넣는다.
	void pushItem(ITEM_TYPE type, vector3 pos);			//아이템을 넣는다.
	void pushWeapon(WEAPON_TYPE type, vector3 pos);		//무기를 넣는다.

	void popObject(int index);							//오브젝트를 삭제한다.
};

