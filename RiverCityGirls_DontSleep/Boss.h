#pragma once
#include "gameNode.h"
#include "GameObject.h"
#include "Enemy.h"

class Enemy;
class Player;
class StageManager;
class ObjectManager;
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

//���� ����
enum class BS_DEST 
{
	RIGHT,
	LEFT
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
	
	IBossState* _right;			//���� ����
	IBossState* _left;			//���� ����

	BS_DEST _dest;
	BS_STATE _state;
	ENEMY_TYPE _ENEMY_TYPE;
	

	/*			//���� ����ü (�������)
	GameObject _obj;
	StageManager* _stageM;
	ObjectManager* _objectM;
	Player* _player;
	Enemy* _enemy;*/
	

	RECT _rcAttack;
	bool _isAttack;
	bool _isDown;
	bool _isWait;
	bool _isPhase;
	bool _isBlock;
	bool _isMove;
	bool _isElbow;
	bool _isMeteor;
	bool _isSmash;
	bool _isHowling;
	bool _isDash;

	   
public:
	Boss() {};
	~Boss() {};
	virtual HRESULT init();			//�ʱ�ȭ
	virtual void release();			//����
	virtual void update();			//����
	virtual void render();			//����

	//������===================================================
	Player* getPlayerAddress() { return _player; }	
	GameObject* getObj() { return &_obj; }
	GameObject getobj() { return _obj; }
	bool getIsDown() { return _isDown; }
	bool getIsWait() { return _isWait; }
	bool getIsPhase() { return _isPhase; }
	bool getIsBlock() { return _isBlock; }
	bool getIsAttack() { return _isAttack; }
	bool getIsMove() { return _isMove; }
	bool getIsElbow() { return _isElbow; }
	bool getIsMeteor() { return _isMeteor; }
	bool getIsSmash() { return _isSmash; }
	bool getIsHowling() { return _isHowling; }
	bool getIsDash() { return _isDash; }
	
	//������===================================================
	void SetState(BS_STATE state);
	void SetDest(BS_DEST dest);
	void setPosition(vector3 pos) { _obj.pos = pos; }	
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }

	//����Լ�===================================================

	void setImage();
	void stageInit();
	void MovePos(float x, float z, float y);				//��ǥ �̵�
	void ChangeImg(string imgName);						//�̹�������

};

