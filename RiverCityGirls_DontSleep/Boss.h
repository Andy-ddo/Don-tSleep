#pragma once
#include "Enemy.h"

class IBossState;

enum class BS_STATE : int
{
	IDLE,			//�⺻
	WAIT,			//���
	MOVE,			//�ȱ�	
	
	BLOCK,			//����	
	ATTACKED,		//�ǰ�
	GROGGY,			//�׷α�		
	PHASE,			//������
	DOWN,			//������
	DEATH,			//���

	HOWLING,		//�Ͽ︵ ����
	METEOR,			//���׿� ����
	DASH,			//�뽬 ����
	ELBOW,			//������ ����
	SLAP,			//�չٴ� ����
	SMASH,			//���Ž� ����
	STANDATTACK		//��� ����	
	
};

class Boss : public Enemy
{
private:
	//���� Ŭ����
	IBossState*	_BState;		//���� ����
	IBossState*	_idle;			//�⺻
	IBossState*	_wait;			//���
	IBossState*	_move;			//�ȱ�	

	IBossState*	_block;			//����	
	IBossState*	_attacked;		//�ǰ�
	IBossState*	_groggy;		//����	
	IBossState* _phase;			//������2
	IBossState*	_down;			//������
	IBossState*	_death;			//���
	
	IBossState*	_howling;		//�Ͽ︵ ����
	IBossState*	_meteor;		//���׿� ����
	IBossState*	_dash;			//�뽬 ����
	IBossState*	_elbow;			//������ ����
	IBossState*	_slap;			//�չٴ� ����
	IBossState*	_smash;			//���Ž� ����
	IBossState*	_standattack;	//��� ����
	
	
	BS_STATE _state;
	ENEMY_TYPE _ENEMY_TYPE;	
	float _frameTimer;

	   
public:
	Boss() {};
	~Boss() {};
	virtual HRESULT init();			//�ʱ�ȭ
	virtual void release();			//����
	virtual void update();			//����
	virtual void render();			//����

	//������===================================================
	//������===================================================
	void SetState(BS_STATE state);
	void SetDest(DIRECTION dest);
	void setPosition(vector3 pos) { _obj.pos = pos; }	
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	

	//����Լ�===================================================
	void playFrame(int count);
	void frameUpdate();
	//void setFrame(FRAMETYPE _frametype);
	void MovePos(float x, float z, float y);				//��ǥ �̵�
	void ChangeImg(string imgName);						//�̹�������
	
};

