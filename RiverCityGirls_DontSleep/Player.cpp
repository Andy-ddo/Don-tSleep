#include "stdafx.h"
#include "Player.h"

#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"

#include "IPlayerState.h"
#include "playerIdle.h"
#include "playerWait.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerJump.h"
#include "playerStick.h"
#include "playerLadder.h"
#include "playerGuard.h"
#include "playerRoll.h"
#include "playerHit.h"
#include "playerStun.h"
#include "playerStand.h"
#include "playerDown.h"
#include "playerDead.h"
#include "playerStomp.h"
#include "playerCombo1.h"
#include "playerCombo2.h"
#include "playerCombo3.h"
#include "playerSAttack.h"
#include "playerDashAttack.h"
#include "playerDashSAttack.h"
#include "playerJumpAttack.h"
#include "playerSAttackDown.h"

HRESULT Player::init()
{
	/*====================================================================
		�÷��̾��� ������Ʈ �ʱ�ȭ�� �⺻ ������ �մϴ�.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wallet"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2));
	_obj.imgIndex = { 0,0 };	//���� �ִϸ��̼��� ��������� �ʾ� �ӽ÷� �صξ����ϴ�.

	//�⺻ ���� �ʱ�ȭ
	{
	_info.jumpPower = 0;
	_info.speed = 4.f;
	_info.hasMember = false;
	_info.isDead = false;
	_info.isControl = true;
	_info.isConDest = true;
	_info.isSky = false;
	_info.hasMember = false;
	_info.dest = DIRECTION::RIGHT;
	_info.moveDest = MOVE_DIRECTION::RIGHT;

	_info.hitCount = 3;
	}

	//�������� ���
	{
	_idle = new playerIdle;
	_wait = new playerWait;
	_walk = new playerWalk;
	_run = new playerRun;
	_jump = new playerJump;
	_stick = new playerStick;
	_ladder = new playerLadder;

	_guard = new playerGuard;
	_roll = new playerRoll;
	_hit = new playerHit;
	_stun = new playerStun;
	_stand = new playerStand;
	_down = new playerDown;
	_dead = new playerDead;

	_stomp = new playerStomp;
	_combo1 = new playerCombo1;
	_combo2 = new playerCombo2;
	_combo3 = new playerCombo3;

	_sAttack = new playerSAttack;
	_dashAttack = new playerDashAttack;
	_dashSAttack = new playerDashSAttack;
	_jumpAttack = new playerJumpAttack;
	_SAttackDown = new playerSAttackDown;
	}
	setState(PL_STATE::WAIT);


	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	//Ű�Է�
	keyInput();
	//�߷��ۿ�
	gravity();
	//���¾�����Ʈ
	_IState->UpdateState();

	_obj.update();
}

void Player::render()
{
	/*====================================================================
		Z-ORDER�� ���� ���� ������ ���� ��ŵ�ϴ�.
	====================================================================*/
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
	Rectangle(getMapDC(), _obj.shadow.rc);
	//(���� �÷��̾� �ִϸ��̼��� ���� �ӽ÷� �صξ����ϴ�. ���߿� ANI_RENDER�� �ٲ㼭 ������!)
}




void Player::setState(PL_STATE state)
{
	if (_info.state == state)return; //���� ���¸� �������� �ʴ´�.
	_info.state = state;

	//���¸� �������´�
	if (_IState != NULL)_IState->ExitState();

	//���¸� �����Ѵ�
	switch (_info.state)
	{
		//�⺻����
	case PL_STATE::IDLE:	    _IState = _idle;		 break;
	case PL_STATE::WAIT:	    _IState = _wait;		 break;
	case PL_STATE::WALK:	    _IState = _walk;		 break;
	case PL_STATE::RUN:		    _IState = _run;			 break;
	case PL_STATE::JUMP:	    _IState = _jump;		 break;
	case PL_STATE::STICK:	    _IState = _stick;		 break;
	case PL_STATE::LADDER:      _IState = _ladder;		 break;
		//���� �� �ǰ�
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:
		_IState = _stand;
		_info.hitCount = 3;
		break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// ����
	case PL_STATE::STOMP:	    _IState = _stomp;		 break;
	case PL_STATE::COMBO1:	    _IState = _combo1;		 break;
	case PL_STATE::COMBO2:	    _IState = _combo2;		 break;
	case PL_STATE::COMBO3:	    _IState = _combo3;		 break;
	case PL_STATE::SATTACK:     _IState = _sAttack;		 break;
	case PL_STATE::DASHATTACK:  _IState = _dashAttack;	 break;
	case PL_STATE::DASHSATTACK: _IState = _dashSAttack;  break;
	case PL_STATE::JUMPATTACK:  _IState = _jumpAttack;	 break;
	case PL_STATE::SATTACKDOWN: _IState = _SAttackDown;  break;
	default: break;
	}

	//���� ��ũ
	_IState->LinkPlAddress(this);
	_IState->EnterState();
}


void Player::stageInit()
{
	/*====================================================================
		���������� �ٲ� ������ �ʱ�ȭ��Ű�� �Լ��Դϴ�.
	====================================================================*/

	/*====================================================================
		��ũ : ���ʹ̸Ŵ���, ������Ʈ �Ŵ����� ��ũ�մϴ�.
	====================================================================*/
	_enemyM = _stageM->getStage()->getEnemyM();
	_objectM = _stageM->getStage()->getObjectM();
}

//�߷��ۿ�
void Player::gravity()
{
	_info.jumpPower -= GRAVITYVALUE;
	if (_obj.pos.y >= 0 && _info.isSky == true)
	{
		//�������°� �ȱ⳪ �ٱ��϶��� �������� �״�� ���� ����
		if (_info.preState == PL_STATE::WALK || _info.preState == PL_STATE::RUN)setState(_info.preState);
		else setState(PL_STATE::IDLE);
		_info.isSky = false;

	}
	//�׸��� ������ ������ �� ����ó��
	if (_obj.pos.y > 0) _info.jumpPower = 0;
	//��ǥ ����
	MovePos(0, 0, _info.jumpPower);
}

void Player::keyInput()
{

	//Ű������ ���ϴ� ���¶�� ����
	if (!_info.isControl)return;

	//����Ű�ޱ�(Ŀ�ǵ带����)
	if (KEY_M->isOnceKeyDownV('D'));

	//����
	if (KEY_M->isOnceKeyDownV('A') && !_info.isSky)
	{
		//�������� ����
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWERVALUE;
		MovePos(0, 0, JUMPPOWERVALUE);
		//�����Ŀ��� - �� �������·� ��ȯ
		if (_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
	}

	//���������� ���ϴ� ���¶�� ����
	if (!_info.isConDest)return;

	//��
	if (KEY_M->isOnceKeyDownV(VK_LEFT))
	{
		_info.moveDest = MOVE_DIRECTION::LEFT;
		_info.dest = DIRECTION::LEFT;
	}
	//��
	if (KEY_M->isOnceKeyDownV(VK_RIGHT))
	{
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
	}
	//��
	if (KEY_M->isOnceKeyDownV(VK_UP))_info.moveDest = MOVE_DIRECTION::UP;
	//�Ʒ�
	if (KEY_M->isOnceKeyDownV(VK_DOWN))_info.moveDest = MOVE_DIRECTION::DOWN;

	//ŰĿ�ǵ� 
	if (!_info.isSky && KEY_M->getVKeyBuffer().size() >= 3)
	{
		//�ٶ󺸴� ����Ű+ �� + d Ŀ�ǵ� ����
		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_RIGHT && _info.dest == DIRECTION::RIGHT)
			cout << "��" << endl;

		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_LEFT && _info.dest == DIRECTION::LEFT)
			cout << "��" << endl;
	}
	
}

void Player::ChangeImg(string imgName)
{
	_obj.img = IMG_M->findImage(imgName);
	//_obj.img->setFrameY((int)_info.indexDest);//���⸻�� �����ӷ������־����
	//if (_info.indexDest == DIRECTION::LEFT) _obj.img->setFrameX(0);
	//else if (_info.indexDest == DIRECTION::RIGHT) _obj.img->setFrameX(_obj.img->getMaxFrameX());

	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}

		_obj.img->setFrameY((int)_obj.imgIndex.y);//���⸻�� �����ӷ������־����
	if (_info.dest == DIRECTION::LEFT) _obj.img->setFrameX(0);
	else if (_info.dest == DIRECTION::RIGHT) _obj.img->setFrameX(_obj.img->getMaxFrameX());

}

//��ǥ�̵�
void Player::MovePos(float x, float z, float jumpPower)
{
	_obj.prePos = _obj.pos;

	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//�׸��ڸ� �ϴ� �ѹ� ������Ʈ
	_obj.shadowUpdate();
	//�浹ó��
	_colM->Collision();

	//�׸��� �Ʒ��� �� ���������� ����ó��
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//���� ��Ʈ ����
	_obj.update();
}
