#pragma once
#include "gameNode.h"
#include "GameObject.h"
#define GRAVITYVALUE 0.5f;       //�߷¼�ġ
#define JUMPPOWERVALUE 15.f		 //�����Ŀ���ġ
#define FRAMEINTERVAL 0.1f		 //���������͹�

//���漱��
class Player;
class StageManager;
class ObjectManager;

class IEnemyState;                 // ���漱��

enum class EN_STATE
{
	EN_IDLE,                       //�⺻
	EN_WALK,					   //�ȱ�
	EN_RUN,						   //�ٱ�
	EN_JUMP,					   //����
	EN_LADDER,					   //��ٸ�
	EN_LADDERTRANSITION,		   //��ٸ� ������ ¤�� ����
	EN_PATROL,					   //�Դٰ���
	EN_STUN,					   //����
	EN_BEGGING,					   //����
	EN_DIE,						   //���
	EN_GUARD,					   //���
	EN_HELDRELEASE,				   //������ ������
	EN_FRIEND,                     //�÷��̾� ���ᰡ ��

	EN_RUNATTACK,				   //�ٴٰ� ����
	EN_JUMPATTACK,				   //���� ����
	EN_HARDATTACK,				   //�� ����
	EN_ATTACK1,					   //ó�� ����
	EN_ATTACK2,					   //ó�� ���� ���� ����
	EN_ATTACK3,					   //ó�� ���� ���� ���� ���� ����

	EN_DOWN,					   //������
	EN_HELDHIT,					   //���� ���� ����
	EN_HIT,						   //����
	EN_WEAPONHIT,				   //����� ����

	EN_WATTACK,                    //����+����
	EN_WIDLE,					   //����+�⺻
	EN_WPICKUP,					   //����+ȹ��
	EN_WRUN,					   //����+�ٱ�
	EN_WTHROW,					   //����+������
	EN_WWALK,					   //����+�ȱ�
};
class Enemy : public gameNode
{
protected:

	GameObject _obj;

	struct tagInfo
	{
	public:
		RECT rcDamage;                //�ǰ� ���� ��Ʈ 
		RECT rcAttack;				   //���� ���� ��Ʈ 

		float gravity;               //�߷�
		float angle;                 //����
		float attack;                 //���ݷ�
		float baseSpeed;              //���� ���ǵ�
		float speed;                  //�̵��ӵ�
		float jumpPower;              //������
		float frameTimer;            //�����ӽð� Ÿ�̸�
		float hp;					//ü��

		bool isDead;               //�׾���
		bool weapon;              //��������
		bool goRight;              //���������� �����ִ�
		bool isAttack;				//�����ߴ�
		bool isSky;                 //���߿� �ִ�
	};
	

	//tagInfo _info;                  //���ʹ� ����

	IEnemyState* _EState;
	IEnemyState* _ES_IDLE;
	IEnemyState* _ES_WALK;
	IEnemyState* _ES_RUN;
	IEnemyState* _ES_JUMP;
	IEnemyState* _ES_LADDER;
	IEnemyState* _ES_LADDERTRANSITION;
	IEnemyState* _ES_PATROL;
	IEnemyState* _ES_STUN;
	IEnemyState* _ES_BEGGING;
	IEnemyState* _ES_DIE;
	IEnemyState* _ES_GUARD;
	IEnemyState* _ES_HELDRELEASE;
	IEnemyState* _ES_FRIEND;
	IEnemyState* _ES_RUNATTACK;
	IEnemyState* _ES_JUMPATTACK;
	IEnemyState* _ES_HARDATTACK;
	IEnemyState* _ES_ATTACK1;
	IEnemyState* _ES_ATTACK2;
	IEnemyState* _ES_ATTACK3;
	IEnemyState* _ES_DOWN;
	IEnemyState* _ES_HELDHIT;
	IEnemyState* _ES_HIT;
	IEnemyState* _ES_WEAPONHIT;
	IEnemyState* _ES_WATTACK;
	IEnemyState* _ES_WIDLE;
	IEnemyState* _ES_WPICKUP;
	IEnemyState* _ES_WRUN;
	IEnemyState* _ES_WTHROW;
	IEnemyState* _ES_WWALK;

	DIRECTION _dest;
	ENEMY_TYPE _ENEMY_TYPE;
	EN_STATE _state;               //���� ���� enum
<<<<<<< HEAD
		
	float _runSpeed;               //�ٴ� �̵� �ӵ� 
	float _walkSpeed;			   //�ȴ� �̵� �ӵ�
	float _jumpPower;              //������
=======

	//int _imageXIndex;			//�̹��� ���� �ε���
	//int _imageYIndex;			//�̹��� ���� �ε���
>>>>>>> origin/수현작업
	

	StageManager* _stageM;		//�������� �Ŵ��� ��ũ
	ObjectManager* _objectM;	//������Ʈ �Ŵ��� ��ũ
	Player* _player;			//�÷��̾�

	tagInfo _info;			//����,���ʹ� ���� ����ü

public:
	virtual HRESULT init(); 
	virtual void release();
	virtual void update();
	virtual void render();

	/*====================================================================
									GETTER
	====================================================================*/
	Player* getPlayerAddress() { return _player; }
	tagInfo&    getInfo() { return _info; }
	GameObject* getObj() { return &_obj; }

	DIRECTION& getdest() { return _dest; }

	GameObject& getRefObj() { return _obj; }

	/*====================================================================
									SETTER
	====================================================================*/
	virtual void setLinkStageM(StageManager* stageM) { _stageM = stageM; }

	virtual void setPosition(vector3 pos) { _obj.pos = pos; }
	virtual void setDest(DIRECTION dest) { _dest = dest; }
	virtual void setGoRight(bool go) { _info.goRight = go; }
	virtual void setIsAttack(bool attack) { _info.isAttack = attack; }
	virtual void SetState(EN_STATE state);
	virtual void setSpeed(float speed) { _info.speed = speed; }

	/*====================================================================
									FUNCTION
	====================================================================*/
	virtual void xzyMove(int x,int z, int y);
	virtual void SetImage();
	virtual void setFrame(int count, float frameInterval);
	virtual void playFrame();
	//virtual void setBool();
};

