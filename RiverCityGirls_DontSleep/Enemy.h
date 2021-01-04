#pragma once
#include "gameNode.h"
#include "GameObject.h"

class Player;
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

	bool _isDead;
	bool _weapon;
	bool _goRight;
	bool _isAttack;				//�����ߴ�

	RECT _rcDamage;      //�ǰ� ���� ��Ʈ
	RECT _rcAttack;		 //���� ���� ��Ʈ
	

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
	Player* _Pl;
	ENEMY_TYPE _ENEMY_TYPE;
	EN_STATE _state;               //���� ���� enum

	int _imageXIndex;			//�̹��� ���� �ε���
	int _imageYIndex;			//�̹��� ���� �ε���
	float _runSpeed;               //�ٴ� �̵� �ӵ� 
	float _walkSpeed;			   //�ȴ� �̵� �ӵ�
	float _jumpPower;              //������
	
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void xzyMove(int x,int z, int y);
	void setPosition(vector3 pos) { _obj.pos = pos; }

	void setDest(DIRECTION dest) { _dest = dest; }
	void setGoRight(bool go) { _goRight = go; }
	void setIsAttack(bool attack) { _isAttack = attack; }

	Player* getPlayerAddress() { return _Pl; }
	bool getIsDead() { return _isDead; }
	bool getWeapon() { return _weapon; }
	bool& getGoRight() { return _goRight; }
	float& getRunSpeed() { return _runSpeed; }
	float& getWalkSpeed() { return _walkSpeed; }

	GameObject* getObj() { return &_obj; }
	void SetState(EN_STATE state);
	void SetImage();
	void imageRedraw();
	void FramePlay(int count);
};

