#pragma once
#include "gameNode.h"
#include "IBossState.h"
#include "Enemy.h"

#define PI 3.14159f

enum class BS_STATE : int
{
	IDLE,			//�⺻
	WAIT,			//���
	WALK,			//�ȱ�	
	
	GUARD,			//����	
	ATTACKED,		//�ǰ�
	GROGGY,			//�׷α�		
	PHASE,			//������
	DOWN,			//������
	DEAD,			//���

	HOWLING,		//�Ͽ︵ ����
	METEOR,			//���׿� ����
	DASH,			//�뽬 ����
	ELBOW,			//������ ����
	SLAB,			//�չٴ� ����
	SMASH,			//���Ž� ����
	STANDATTACK		//��� ����	
	
};

//���� ����
enum class BS_DEST : int
{
	RIGHT,
	LEFT
};

//���漱��
class IBossState;	//���� ����

class Boss : public Enemy
{
private:

	//���� ����ü
	struct tagInfo
	{
	public:
		image* img;
		int count;
		float angle;
		float bsWidth, bsHeight;	//�׸��� ���μ���
		float bWidth, bHeight;		//�÷��̾� ���μ���
		float x, z, y;				//��ǥ
		float jumpPower;			//�����Ŀ�
		float speed;				//�ӵ�
		float damage;				//������		
		bool isAttack;				//���� ���� ����
		bool isDead;				//�������		
		RECT bssRc;					//�׸��� ��Ʈ
		RECT bsRc;					//���� ��Ʈ
		BS_STATE state;				//���� ����
		BS_DEST dest;				//����
	};

	tagInfo _info;		
	

private:
	//���� Ŭ����
	IBossState*	_IState;		//���� ����
	IBossState*	_idle;			//�⺻
	IBossState*	_wait;			//���
	IBossState*	_walk;			//�ȱ�	

	IBossState*	_guard;			//����	
	IBossState*	_attacked;		//�ǰ�
	IBossState*	_groggy;		//����	
	IBossState* _phase;			//������2
	IBossState*	_down;			//������
	IBossState*	_dead;			//���
	
	IBossState*	_howling;		//�Ͽ︵ ����
	IBossState*	_meteor;		//���׿� ����
	IBossState*	_dash;			//�뽬 ����
	IBossState*	_elbow;			//������ ����
	IBossState*	_slab;			//�չٴ� ����
	IBossState*	_smash;			//���Ž� ����
	IBossState*	_standattack;	//��� ����


public:
	//�⺻�Լ�===================================================
	virtual HRESULT init();			//�ʱ�ȭ
	virtual void release();			//����
	virtual void update();			//����
	virtual void render();			//����

	//������===================================================
	tagInfo& GetInfo() { return _info; }
	RECT&	 GetSRc() { return _info.bssRc; }
	RECT&	 GetRc() { return _info.bsRc; }

	//������===================================================
	void SetState(BS_STATE state);

	//����Լ�===================================================
	void MovePos(float x, float z, float y);				//��ǥ �̵�
	void SetAI();										//AI ����
	void ChangeImg(string imgName);						//�̹�������

};

