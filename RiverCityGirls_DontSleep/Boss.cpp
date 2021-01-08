#include "stdafx.h"

#include "Boss.h"
#include "bossMeteor.h"
#include "bossAttacked.h"
#include "bossBlock.h"
#include "bossDashAttack.h"
#include "bossDeath.h"
#include "bossDown.h"
#include "bossElbowAttack.h"
#include "bossGroggy.h"
#include "bossHowling.h"
#include "bossIdle.h"
#include "bossWait.h"
#include "bossMove.h"
#include "bossPhase2.h"
#include "bossSlapAttack.h"
#include "bossSmashAttack.h"
#include "bossStandAttack.h"
#include "IBossState.h"

#include "StageManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"

HRESULT Boss::init()
{
	_player = _stageM->getPlayer();
	_objectM = _stageM->getStage()->getObjectM();

	_obj.init(OBJECT_GROUP::BOSS, IMG_M->findImage("Bs_idle"), _obj.pos);	
	_obj.imgIndex = { 0,0 }; 
	
	_frameTimer = TIME_M->getWorldTime();

	//�������� ���
	_idle = new bossIdle;
	_wait = new bossWait;
	_move = new bossMove;

	_block = new bossBlock;
	_attacked = new bossAttacked;
	_groggy = new bossGroggy;
	_down = new bossDown;
	_death = new bossDeath;
	_phase = new bossPhase2;

	_howling = new bossHowling;
	_meteor = new bossMeteor;
	_dash = new bossDashAttack;
	_elbow = new bossElbowAttack;
	_slap = new bossSlapAttack;
	_smash = new bossSmashAttack;
	_standattack = new bossStandAttack;

	_BState = NULL;
	SetState(BS_STATE::IDLE);
		
	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	_obj.update();
	setImage();
	_BState->UpdateState();	
	frameUpdate();
	if (_player->getObj().pos.x < _obj.pos.x)
	{
		SetDest(DIRECTION::LEFT);
	}
	else if(_player->getObj().pos.x < _obj.pos.x)
	{
		SetDest(DIRECTION::RIGHT);
	}	
}

void Boss::render()
{
}

void Boss::SetState(BS_STATE state)
{
	if (_BState != NULL && _state == state) return; //���� ���¸� �������� �ʴ´�.
	_state = state;

	//���¸� �������´�
	if (_BState != NULL)_BState->ExitState();

	//���¸� �����Ѵ�
	switch (_state)
	{
		//�⺻����
	case BS_STATE::IDLE:	    _BState = _idle;		 break;
	case BS_STATE::WAIT:	    _BState = _wait;		 break;
	case BS_STATE::MOVE:	    _BState = _move;		 break;
	
		//���� �� ���º�ȭ
	case BS_STATE::BLOCK:       _BState = _block;		 break;
	case BS_STATE::ATTACKED:    _BState = _attacked;	 break;
	case BS_STATE::GROGGY:      _BState = _groggy;		 break;	
	case BS_STATE::DOWN:	    _BState = _down;		 break;
	case BS_STATE::DEATH:	    _BState = _death;		 break;
	case BS_STATE::PHASE:		_BState = _phase;	     break;

		// ����
	case BS_STATE::HOWLING:		_BState = _howling;		 break;
	case BS_STATE::METEOR:		_BState = _meteor;		 break;
	case BS_STATE::DASH:		_BState = _dash;		 break;
	case BS_STATE::ELBOW:		_BState = _elbow;		 break;
	case BS_STATE::SLAP:		_BState = _slap;		 break;
	case BS_STATE::SMASH:		_BState = _smash;		 break;
	case BS_STATE::STANDATTACK: _BState = _standattack;  break;
	default: break;
	}

	//���� ��ũ
	_BState->LinkBSAddress(this);
	_BState->EnterState();
}

void Boss::SetDest(DIRECTION dest)
{
	if (_dest == dest)return; //���� ���¸� �������� �ʴ´�.
	_dest = dest;
}

void Boss::frameUpdate()
{
	if (TIME_M->getWorldTime() - _frameTimer > 0.1f)
	{
		_frameTimer = TIME_M->getWorldTime();

		switch (_state)
		{
		case BS_STATE::IDLE:		
		case BS_STATE::DEATH:
		case BS_STATE::MOVE:
		playFrame(0);
		break;
		
		case BS_STATE::METEOR:
		case BS_STATE::DASH:
		playFrame(1);
		break;

		case BS_STATE::SMASH:
		case BS_STATE::SLAP:
		case BS_STATE::ELBOW:
		case BS_STATE::PHASE:
		case BS_STATE::HOWLING:
		case BS_STATE::ATTACKED:		
		case BS_STATE::STANDATTACK:
		playFrame(-1);
		break;

		default:
		break;
		}
	}
}

void Boss::playFrame(int count)
{
	switch (count)
	{
	case -1:	//�� �� ��� �� �⺻
		if (_dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX()) SetState(BS_STATE::IDLE);
		else if (_dest == DIRECTION::LEFT && _obj.imgIndex.x < 0) SetState(BS_STATE::IDLE);
		break;
	case 1:		//�� ���� ���
		if (_dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX()) _obj.imgIndex.x = _obj.img->getMaxFrameX();
		else if (_dest == DIRECTION::LEFT && _obj.imgIndex.x < 0) _obj.imgIndex.x = 0;
		break;
	case 0:		//���� ���
		if (_dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX()) _obj.imgIndex.x = 0;
		else if (_dest == DIRECTION::LEFT && _obj.imgIndex.x < 0) _obj.imgIndex.x = _obj.img->getMaxFrameX();
		break;
	}

	if (_obj.imgIndex.x < 0) _obj.imgIndex.x = 0;
	else if (_obj.imgIndex.x > _obj.img->getMaxFrameX()) _obj.imgIndex.x = _obj.img->getMaxFrameX();
		
	switch (_dest)
	{
	case DIRECTION::RIGHT: 
		++_obj.imgIndex.x;
		_obj.imgIndex.y = 1;
		break;
		
	case DIRECTION::LEFT: 
		--_obj.imgIndex.x;
		_obj.imgIndex.y = 0;
		break;
	}
}

/*void Boss::setFrame(FRAMETYPE _frametype)
{
	switch (_dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}
	_obj.img->setFrameY((int)_dest);

	//������ ���� �ð� ����
	if (TIME_M->getWorldTime() - _frameTimer > 1.0f)
	{		
		_frameTimer = TIME_M->getWorldTime();
		switch (_dest)
		{
		case DIRECTION::LEFT:
			if (_frametype != FRAMETYPE::REVERSROOP && _frametype != FRAMETYPE::REVERSONCE) ++_obj.imgIndex.x;
			else --_obj.imgIndex.x;


			break;
		case DIRECTION::RIGHT:
			if (_frametype != FRAMETYPE::REVERSROOP&& _frametype != FRAMETYPE::REVERSONCE) --_obj.imgIndex.x;
			else  ++_obj.imgIndex.x;
			break;
		}
	}

	//������ x ��ȣ ����
	switch (_frametype)
	{
	case FRAMETYPE::ONCE://�� �� ���
	{
		//������ ��� x�ε����� 0������~ �������� �������� �� �Ǹ� ����ȣ�� �����ӹ�ȣ ����
		if (_dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		//�������� ��� x�ε����� �������� 0������ �������� �� �Ǹ� 0������ ������ ��ȣ ����
		else if (_dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0; return;
		}

	}
	break;
	case FRAMETYPE::ROOP://���� ���
	{
		//������ ��� x�ε����� 0������~ �������� �������� �� �Ǹ� ����ȣ�� �����ӹ�ȣ 0������ ����
		if (_dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		//�������� ��� x�ε����� �������� 0������ �������� �� �Ǹ� 0������ ������ ��ȣ ����ȣ�� ����
		else if (_dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
	}
	break;
	case FRAMETYPE::REVERSONCE://�ݴ� �ѹ� ���
	{
		if (_dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		else if (_dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0; return;
		}
	}
	break;
	case FRAMETYPE::REVERSROOP://�ݴ� ���� ���
	{
		if (_dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		else if (_dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();

	}
	break;
	}
}*/

void Boss::setImage()
{
	switch (_state)
	{
	case BS_STATE::IDLE:
		_obj.img = IMG_M->findImage("Bs_idle");
	break;
	case BS_STATE::WAIT:
		_obj.img = IMG_M->findImage("Bs_wait");
	break;
	case BS_STATE::MOVE:
		_obj.img = IMG_M->findImage("Bs_move");
	break;
	case BS_STATE::BLOCK:
		_obj.img = IMG_M->findImage("Bs_block");
	break;
	case BS_STATE::ATTACKED:
		_obj.img = IMG_M->findImage("Bs_attacked"); 
	break;
	case BS_STATE::GROGGY:
		_obj.img = IMG_M->findImage("Bs_groggy"); 
	break;
	case BS_STATE::PHASE:
		_obj.img = IMG_M->findImage("Bs_phase"); 
	break;
	case BS_STATE::DOWN:
		_obj.img =  IMG_M->findImage("Bs_down"); 
	break;
	case BS_STATE::DEATH:
		_obj.img = IMG_M->findImage("Bs_death"); 
	break;
	case BS_STATE::HOWLING:
		_obj.img = IMG_M->findImage("Bs_howling"); 
	break;
	case BS_STATE::METEOR:
		_obj.img = IMG_M->findImage("Bs_meteor"); 
	break;
	case BS_STATE::DASH:
		_obj.img = IMG_M->findImage("Bs_dash"); 
	break;
	case BS_STATE::ELBOW:
		_obj.img = IMG_M->findImage("Bs_elbow"); 
	break;
	case BS_STATE::SLAP:
		_obj.img = IMG_M->findImage("Bs_slap"); 
	break;
	case BS_STATE::SMASH:
		_obj.img = IMG_M->findImage("Bs_smash"); 
	break;
	case BS_STATE::STANDATTACK:
		_obj.img = IMG_M->findImage("Bs_standat");
	break;	
	}
}

void Boss::MovePos(float x, float z, float y)
{
	_obj.pos.x += x;	
	_obj.pos.z -= z;
	_obj.pos.y += y;
	
}

void Boss::ChangeImg(string imgName)
{
	_obj.img = IMG_M->findImage(imgName);	
}

