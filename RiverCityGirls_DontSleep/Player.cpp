#include "stdafx.h"
#include "Player.h"
//�ܺ�
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
//����
#include "IPlayerState.h"
#include "playerIdle.h"
#include "playerWait.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerJump.h"
#include "playerStick.h"
#include "playerClimb.h"
#include "playerPick.h"
#include "playerGrab.h"
#include "playerGuard.h"
#include "playerRoll.h"
#include "playerHit.h"
#include "playerStun.h"
#include "playerStand.h"
#include "playerDown.h"
#include "playerDead.h"
#include "playerThrow.h"
#include "playerStomp.h"
#include "playerCombo1.h"
#include "playerCombo2.h"
#include "playerCombo3.h"
#include "playerSAttack.h"
#include "playerDashAttack.h"
#include "playerDashSAttack.h"
#include "playerJumpAttack.h"
#include "playerSAttackDown.h"

//�ʱ�ȭ
HRESULT Player::init()
{
	/*====================================================================
		�÷��̾��� ������Ʈ �ʱ�ȭ�� �⺻ ������ �մϴ�.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wait"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 200));
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
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		_info._frameTimer = TIME_M->getWorldTime();
		_info._ani = new animation;
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
		_climb = new playerClimb;
		_pick = new playerPick;

		_grab = new playerGrab;
		_guard = new playerGuard;
		_roll = new playerRoll;
		_hit = new playerHit;
		_stun = new playerStun;
		_stand = new playerStand;
		_down = new playerDown;
		_dead = new playerDead;

		_throw = new playerThrow;
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

	/*====================================================================
		�׸��� �� �浹 ó���� ���� �� �����մϴ�.
	====================================================================*/

	_shadow.pos = vector3(_obj.pos.x, _obj.pos.y, _obj.pos.z);
	_shadow.rc = RectMakeCenter(_shadow.pos.x, _shadow.pos.z, _obj.img->getWidth(), 20);
	_shadow.LT = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RT = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RB = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z + 10);
	_shadow.LB = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z + 10);
	return S_OK;
}

void Player::release()
{
}

//���� ���� �߿��ԡ� ����->�߷�->Ű�Է�
void Player::update()
{
	//���¾�����Ʈ
	_IState->UpdateState();
	//�߷��ۿ�
	gravity();
	//Ű�Է�
	keyInput();
	//������Ʈ ����
	_obj.update();
	//�ִ������� ����
	if(_info._rendType == RENDERTYPE::ANI_RENDER)
	_info._ani->frameUpdate(TIME_M->getElapsedTime() * 10);
	//�����Ӿ���
	playFrame();

}

//����
void Player::render()
{
	/*====================================================================
		Z-ORDER�� ���� ���� ������ ���� ��ŵ�ϴ�.
	====================================================================*/

	ZORDER_M->renderObject(getMapDC(), &_obj, _info._rendType);
	Rectangle(getMapDC(), _obj.shadow.rc);
}

//���� ����
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
	case PL_STATE::CLIMB:      _IState = _climb;		 break;
	case PL_STATE::PICK:      _IState = _pick;		 break;
		//���� �� �ǰ�
	case PL_STATE::GRAB:       _IState = _grab;		 break;
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::ROLL:       _IState = _roll;		 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:		_IState = _stand;
		_info.hitCount = 3;
		break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// ����
	case PL_STATE::THROW:	    _IState = _throw;		 break;
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

//���������� �ٲ� ������ �ʱ�ȭ��Ű�� �Լ�
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

//�̹��� ����
void Player::changeImg(string imgName, bool reverse)
{
	//�̹����� �ٲ۴�.
	_obj.img = IMG_M->findImage(imgName);
	//������ �ð� �����Ͽ� �ٷ� ������ ����
	_info._frameTimer = TIME_M->getWorldTime();
	//����� ������ ���� ���� ������ x �ε��� ����
	switch (_info.dest)
		{
		case DIRECTION::LEFT:
			if(!reverse)_obj.imgIndex.x = 0;
			else if(reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX(); 
			_obj.imgIndex.y = 0;
			break;
			
		case DIRECTION::RIGHT:
			if (!reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX(); 
			else if (reverse)_obj.imgIndex.x =0;
			_obj.imgIndex.y = 1;
			break;
		}

	
}

//������ ����
void Player::setFrame(FRAMETYPE frameType, float frameInterval)
{
	//������ y ��ȣ ����
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}

	//������ y ��ȣ ����
	_obj.img->setFrameY((int)_info.dest);

	//������ x ��ȣ ����
	switch (frameType)
	{
	case FRAMETYPE::ONCE://�� �� ���
		{
		//������ ��� x�ε����� 0������~ �������� �������� �� �Ǹ� ����ȣ�� �����ӹ�ȣ ����
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		//�������� ��� x�ε����� �������� 0������ �������� �� �Ǹ� 0������ ������ ��ȣ ����
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x <= 0)
		{
			_obj.imgIndex.x = 0; return;
		}
			
		}
		break;
	case FRAMETYPE::ROOP://���� ���
		{
		//������ ��� x�ε����� 0������~ �������� �������� �� �Ǹ� ����ȣ�� �����ӹ�ȣ 0������ ����
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		//�������� ��� x�ε����� �������� 0������ �������� �� �Ǹ� 0������ ������ ��ȣ ����ȣ�� ����
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x <= 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
		break;
	case FRAMETYPE::REVERSONCE://�ݴ� �ѹ� ���
		{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0)
		{
			_obj.imgIndex.x = 0; return;
		}
		}
		break;
	case FRAMETYPE::REVERSROOP://�ݴ� ���� ���
		{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		
		}
		break;
	}

	cout << _obj.imgIndex.x << endl;

	//������ x ��ȣ ����
	_obj.img->setFrameX(_obj.imgIndex.x);
	


	//������ ���� �ð� ����
	if (TIME_M->getWorldTime() - _info._frameTimer > frameInterval)
	{
		//�ð� ����
		_info._frameTimer = TIME_M->getWorldTime();
		switch (_info.dest)
		{
		case DIRECTION::LEFT:
			if(frameType != FRAMETYPE::REVERSROOP && frameType != FRAMETYPE::REVERSONCE) ++_obj.imgIndex.x;
			else --_obj.imgIndex.x;
			
			
			break;
		case DIRECTION::RIGHT:
			if (frameType != FRAMETYPE::REVERSROOP&& frameType != FRAMETYPE::REVERSONCE) --_obj.imgIndex.x;
			else  ++_obj.imgIndex.x;
			break;
		}
	}
}

//������ ����
void Player::playFrame()
{
	switch (_info.state)
	{
	//������� (�Ϲ� �ӵ�)
	case PL_STATE::WAIT:	case PL_STATE::STUN:
		setFrame(FRAMETYPE::ROOP, FRAMEINTERVAL);
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		break;
	//�ݴ� ������� (����)
	case PL_STATE::RUN:
		setFrame(FRAMETYPE::REVERSROOP, FRAMEINTERVAL*0.35);
		break;
	//�ݴ� �������
	case PL_STATE::IDLE:	case PL_STATE::WALK:
		setFrame(FRAMETYPE::REVERSROOP, FRAMEINTERVAL);
		break;

	//�ѹ� (õõ��)
	case PL_STATE::PICK:	case PL_STATE::GRAB:					 
	
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL +2.f);
		break;
	//�ѹ� (�Ϲ� �ӵ�)
	case PL_STATE::JUMP:	case PL_STATE::STICK:
	case PL_STATE::ROLL:
	case PL_STATE::HIT:		case PL_STATE::STAND:
	case PL_STATE::DOWN:	case PL_STATE::DEAD:
	case PL_STATE::THROW:	case PL_STATE::STOMP:
	case PL_STATE::COMBO1:	case PL_STATE::COMBO2:		
	case PL_STATE::COMBO3:	case PL_STATE::SATTACK:
	case PL_STATE::DASHATTACK:	case PL_STATE::DASHSATTACK:
	case PL_STATE::SATTACKDOWN: case PL_STATE::JUMPATTACK:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL);	
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		break;
	//�ݴ� �ѹ���� (����)
	case PL_STATE::GUARD:
		setFrame(FRAMETYPE::REVERSONCE, FRAMEINTERVAL*0.4);
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		break;
	//�ִϷ���
	case PL_STATE::CLIMB:
		_info._rendType = RENDERTYPE::ANI_RENDER;
		_info._ani->init(_obj.img->getWidth(), _obj.img->getHeight(),
			_obj.img->getFrameWidth(), _obj.img->getFrameHeight());
		break;
	}

}

//��ǥ�̵�
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.prePos = _obj.pos;

	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//�׸��ڸ� �ϴ� �ѹ� ������Ʈ (�浹ó���� ���Ѱ�! �ǵ帮�� �ȵ�!)
	_obj.shadowUpdate();
	//�浹ó�� 
	_colM->objectCollision();

	//�׸��� �Ʒ��� �� ���������� ����ó��
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//���� ��Ʈ ����
	_obj.update();
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
if (_obj.pos.y > 0) _info.jumpPower = 0;
movePos(0, 0, _info.jumpPower);
}

//Ű�Է�
void Player::keyInput()
{
	//Ű������ ���ϴ� ���¶�� ����
	if (!_info.isControl)return;

	//����Ű�ޱ�(Ŀ�ǵ带����)
	if (KEY_M->isOnceKeyDownV('D'));

	//����
	if (KEY_M->isOnceKeyDownV('A')&& !_info.isSky)
	{
		//�������� ����
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWERVALUE;
		movePos(0, 0, JUMPPOWERVALUE);
	//�����Ŀ��� - �� �������·� ��ȯ
	if(_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
	}
	//������
	if (KEY_M->isOnceKeyDownV('W') && !_info.isSky)
	{
		//�������� ����
		_info.preState = _info.state;
		setState(PL_STATE::ROLL);
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

