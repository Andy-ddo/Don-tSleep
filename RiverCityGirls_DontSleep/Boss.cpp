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
	
	_info.angle = PI / 2;
	_info.speed = 3.0f;

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
	
	_isAttack = false;
	_isDown = false;
	_isBlock = false;
	_isDead = false;
	_isPhase = false;
	_isWait = false;
	_isMove = false;
	_isElbow = false;
	_isMeteor = false;
	_isSmash = false;
	_isHowling = false;
	_isDash = false;

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

	if (_player->getObj().pos.x <= _obj.pos.x)
	{
		SetDest(DIRECTION::LEFT);
	}
	else
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
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_block"); }
		break;
		case BS_STATE::ATTACKED:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_attacked"); }
		break;
		case BS_STATE::GROGGY:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_groggy"); }
		break;
		case BS_STATE::PHASE:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_phase"); }
		break;
		case BS_STATE::DOWN:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_down"); }
		break;
		case BS_STATE::DEATH:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_death"); }
		break;
		case BS_STATE::HOWLING:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_howling"); }
		break;
	case BS_STATE::METEOR:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_meteor"); }
		break;
	case BS_STATE::DASH:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_dash"); }
		break;
	case BS_STATE::ELBOW:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_elbow"); }
		break;
	case BS_STATE::SLAP:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_slap"); }
		break;
	case BS_STATE::SMASH:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_smash"); }
		break;
	case BS_STATE::STANDATTACK:
		if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_standat"); }
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

