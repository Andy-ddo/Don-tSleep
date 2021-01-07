#pragma once
#include "gameNode.h"
#include "GameObject.h"
#define GRAVITYVALUE	0.5f			//�߷¼�ġ
#define JUMPPOWERVALUE  15.f			//�����Ŀ���ġ
#define FRAMEINTERVAL	0.1f				//���������͹�

//���漱��
class StageManager;
class ObjectManager;
class EnemyManager;
class IPlayerState;
class CollisionManager;

/*====================================================================
		�÷��̾��Դϴ�. Stage�� ��ũ�Ǿ� �־�,
		���ʹ� �Ŵ���, ������Ʈ �Ŵ����� ����˴ϴ�.
====================================================================*/
//�÷��̾� ���� �̳�
enum class PL_STATE : int
{
	IDLE,			//�⺻
	WAIT,			//���
	WALK,			//�ȱ�
	RUN,			//�޸���
	JUMP,			//����
	STICK,			//�����
	CLIMB,			//������
	PICK,			//�ݱ�

	GRAB,			//���
	GUARD,			//����
	ROLL,			//������
	HIT,			//�ǰ�
	STUN,			//����
	STAND,			//���
	DOWN,			//������
	DEAD,			//���

	THROW,			//������
	STOMP,			//���
	COMBO1,			//�޺�����1
	COMBO2,			//�޺�����2
	COMBO3,			//�޺�����3

	SATTACK,		//������
	DASHATTACK,		//�뽬 ����
	DASHSATTACK,	//�뽬 ������
	JUMPATTACK,		//��������
	SATTACKDOWN		//�ٶ󺸴¹���Ű + �� + ������ (Ŀ�ǵ��Է�)
};

//�÷��̾� ���� �̳�
enum class MOVE_DIRECTION : int
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

//������ ���� Ÿ�� �̳�
enum class FRAMETYPE : int
{
	ONCE,
	ROOP,
	REVERSONCE,
	REVERSROOP
};

class Player: public gameNode
{
private:
	//���� ����ü
	struct tagInfo
	{
	public:
		RECT  plAttackRc;			//�÷��̾� ���ݷ�Ʈ
		float jumpPower;			//�����Ŀ�
		float speed;				//�ӵ�

		bool hasMember;				//�ɹ����� ����
		bool isDead;				//�������
		bool isControl;				//Ű�Է� ���� ����
		bool isConDest;				//������ȯ ���� ����
		bool isSky;					//��� ����

		MOVE_DIRECTION  moveDest;	//�ൿ ����
		DIRECTION dest;				//�ε��� ����
		PL_STATE state;				//�÷��̾� ����
		PL_STATE preState;			//�÷��̾� ��������

		WEAPON_TYPE weaponType;		//��������
		float hp;					//ü��
		float force;				//���ݷ�
		float coin;					//������
		int	   LV;					//����
		float  exp;					//����ġ
		int hitCount;				//�ǰ� ī��Ʈ (3�������� �ٿ��)

		float frameTimer;			//�����ӽð� Ÿ�̸�
		RENDERTYPE rendType;		//����Ÿ��
		animation* ani;			//�⺻ �ִϸ��̼�
		//�ھ����ۺ��ͷ� �κ��丮������ ���Ⱑ�ƴ�����.. ���������� �÷��̱׶����� ���ɼ�����
	};
private:
	tagInfo	   _info;			//�÷��̾� ����
	GameObject _obj;			//���� ������Ʈ

	StageManager* _stageM;		//�������� �Ŵ��� ��ũ
	ObjectManager* _objectM;	//������Ʈ �Ŵ��� ��ũ
	EnemyManager* _enemyM;		//���ʹ� �Ŵ��� ��ũ
	CollisionManager* _colM;
	GameObject*		_platform;
	//�ڸɹ��� ���ʹ̸� ���� ����(�����)

private:
	//���� Ŭ����
	IPlayerState*	_IState;		//���� ����
	IPlayerState*	_idle;			//�⺻
	IPlayerState*	_wait;			//���
	IPlayerState*	_walk;			//�ȱ�
	IPlayerState*	_run;			//�޸���
	IPlayerState*	_jump;			//����
	IPlayerState*	_stick;			//�����
	IPlayerState*	_climb;			//������
	IPlayerState*	_pick;			//�ݱ�

	IPlayerState*	_grab;			//���
	IPlayerState*	_guard;			//����
	IPlayerState*	_roll;			//������
	IPlayerState*	_hit;			//�ǰ�
	IPlayerState*	_stun;			//����
	IPlayerState*	_stand;			//���
	IPlayerState*	_down;			//������
	IPlayerState*	_dead;			//���

	IPlayerState*	_throw;			//������
	IPlayerState*	_stomp;			//���
	IPlayerState*	_combo1;		//�޺�����1
	IPlayerState*	_combo2;		//�޺�����2
	IPlayerState*	_combo3;		//�޺�����3

	IPlayerState*	_sAttack;		//������
	IPlayerState*	_dashAttack;	//�뽬����
	IPlayerState*	_dashSAttack;   //�뽬 ������
	IPlayerState*	_jumpAttack;    //��������
	IPlayerState*	_SAttackDown;   //�ٶ󺸴¹���Ű + �� + ������ (Ŀ�ǵ��Է�)
public:
	Player() {};
	~Player() {};
	virtual HRESULT init();		//�ʱ�ȭ
	virtual void release();		//����
	virtual void update();		//������Ʈ
	virtual void render();		//����

	/*====================================================================
									GETTER
	====================================================================*/
	GameObject getObj() { return _obj; }
	tagInfo    getInfo() { return _info; }
	GameObject* getPObj() { return &_obj; }
	GameObject* getPlatform() { return _platform; }
	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkColM(CollisionManager* colM) { _colM = colM; }
	//���� ����
	void setIsControl(bool control) { _info.isControl = control; }
	//���� ����
	void setState(PL_STATE state);
	//���� ��ȯ ����
	void setIsConDest(bool isConDest) { _info.isConDest = isConDest; }
	void setPlatform(GameObject* platform) { _platform = platform; }
	void setJumpPower(float num) { _info.jumpPower = num;  }
	void setIsSky(bool is) { _info.isSky = is; }
	/*====================================================================
									FUNCTION
	====================================================================*/
	void stageInit();

	//�߷��ۿ�
	void gravity();
	//Ű �Է�
	void keyInput();
	//�̹�������
	void changeImg(string imgName, bool reverse);
	//������ ����
	void setFrame(FRAMETYPE frameType, float frameInterval);
	//������ ����
	void playFrame();
	//��ǥ �̵�
	void movePos(float x, float z, float y);
};
