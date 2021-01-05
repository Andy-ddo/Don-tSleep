#pragma once
#include "gameNode.h"
#include "GameObject.h"
#define GRAVITYVALUE	0.5f			//�߷¼�ġ
#define JUMPPOWERVALUE  15.f			//�����Ŀ���ġ
#define FRAMEINTERVAL	1.f				//���������͹�

//���漱��
class StageManager;
class ObjectManager;
class EnemyManager;
class IPlayerState;

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

//�÷��̾� ���� �̳�
enum class PL_STATE : int
{
	IDLE,			//�⺻
	WAIT,			//���
	WALK,			//�ȱ�
	RUN,			//�޸���
	JUMP,			//����
	STICK,			//�����
	LADDER,			//��ٸ�

	GUARD,			//����
	ROLL,			//������
	HIT,			//�ǰ�
	STUN,			//����
	STAND,			//���
	DOWN,			//������
	DEAD,			//���

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

//������ ���� Ÿ�� �̳�
enum class PL_FRAMETYPE : int
{
	ONCE,
	ROOP
};

class Player: public gameNode
{
private:
	//�÷��̾� ����
	enum class MOVE_DIRECTION : int
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
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

		float _frameTimer;			//�����ӽð� Ÿ�̸�
		//�ھ����ۺ��ͷ� �κ��丮������ ���Ⱑ�ƴ�����.. ���������� �÷��̱׶����� ���ɼ�����
	};
private:
	//�ӽ�?????�ɹ�
	RECT _shadowRc;			//�׸��� ��Ʈ
	vector3 _shadowLT, _shadowRT, _shadowRB, _shadowLB;	//�׸��� ����
	vector3 _shadowPos;		//�׸��� ��ġ
	tagShadow _shadow;		//�׸���
	//========================================================================
private:
	tagInfo	   _info;			//�÷��̾� ����
	GameObject _obj;			//���� ������Ʈ

	StageManager* _stageM;		//�������� �Ŵ��� ��ũ
	ObjectManager* _objectM;	//������Ʈ �Ŵ��� ��ũ
	EnemyManager* _enemyM;		//���ʹ� �Ŵ��� ��ũ

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
	IPlayerState*	_ladder;		//��ٸ�

	IPlayerState*	_guard;			//����
	IPlayerState*	_roll;			//������
	IPlayerState*	_hit;			//�ǰ�
	IPlayerState*	_stun;			//����
	IPlayerState*	_stand;			//���
	IPlayerState*	_down;			//������
	IPlayerState*	_dead;			//���

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

	virtual HRESULT init();		//�ʱ�ȭ
	virtual void release();		//����
	virtual void update();		//������Ʈ
	virtual void render();		//����

	/*====================================================================
									GETTER
	====================================================================*/
	GameObject getObj() { return _obj; }
	tagInfo    getInfo() { return _info; }
	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	//���� ����
	void setIsControl(bool control) { _info.isControl = control; }
	//���� ����
	void setState(PL_STATE state);
	//���� ��ȯ ����
	void setIsConDest(bool isConDest) { _info.isConDest = isConDest; }
	/*====================================================================
									FUNCTION
	====================================================================*/
	void shadowUpdate();
	void stageInit();
	void move();

	//�߷��ۿ�
	void gravity();
	//Ű �Է�
	void keyInput();
	//�̹�������
	void changeImg(string imgName);
	//������ ����
	void playFrame();
	//��ǥ �̵�
	void movePos(float x, float z, float y);

	/*====================================================================
									COLLISION
	====================================================================*/
	void playerObjectCollision();

	// ���� �¿� �浹 ����
	void LRUDCollision(GameObject* cha, tagShadow* sh, GameObject* obj);
	// ���� ����
	void AirCollision(GameObject* cha, tagShadow* sh, GameObject* obj);

};