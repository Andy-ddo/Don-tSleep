#pragma once
#include "gameNode.h"
#include "GameObject.h"

class StageManager;
class Stage;
class ObjectManager;
class EnemyManager;

//�ӽ� �׸��� ����ü (�Ŀ� GameObject������ �Ű��� ����.)
struct tagShadow
{
	RECT rc;
	vector3 LT, RT, RB, LB;
	vector3 pos;
};

/*====================================================================
	�÷��̾��Դϴ�. Stage�� ��ũ�Ǿ� �־�,
	���ʹ� �Ŵ���, ������Ʈ �Ŵ����� ����˴ϴ�.
====================================================================*/

class Player : public gameNode
{

private:
	GameObject _obj;		//���� ������Ʈ

	float _jumpPower;		//������
	float _speed;			//�ӵ�
	int _jumpCount;			//���� Ƚ��

	RECT _shadowRc;			//�׸��� ��Ʈ
	vector3 _shadowLT, _shadowRT, _shadowRB, _shadowLB;	//�׸��� ����
	vector3 _shadowPos;		//�׸��� ��ġ
	tagShadow _shadow;		//�׸���

	StageManager* _stageM;		//�������� �Ŵ��� ��ũ
	ObjectManager* _objectM;	//������Ʈ �Ŵ��� ��ũ
	EnemyManager* _enemyM;		//���ʹ� �Ŵ��� ��ũ

	bool _isControl;				//Ű ��Ʈ���� ��������

public:

	virtual HRESULT init();		//�ʱ�ȭ
	virtual void release();		//����
	virtual void update();		//������Ʈ
	virtual void render();		//����

/*====================================================================
								GETTER
====================================================================*/
	GameObject getObj() { return _obj; }
	
/*====================================================================
								SETTER
====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setIsControl(bool control) { _isControl = control; }

/*====================================================================
								FUNCTION
====================================================================*/
	void move();
	void shadowUpdate();
	void stageInit();
	void keyInput();

/*====================================================================
								COLLISION
====================================================================*/
	void playerObjectCollision();

	// ���� �¿� �浹 ����
	void LRUDCollision(GameObject* cha, tagShadow* sh, GameObject* obj);
	// ���� ����
	void AirCollision(GameObject* cha, tagShadow* sh, GameObject* obj);

};

