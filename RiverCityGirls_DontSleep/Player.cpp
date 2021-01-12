#include "stdafx.h"
#include "Player.h"
//?��?
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "ItemObj.h"
#include "Object.h"
//����
#include "IPlayerState.h"
#include "playerIdle.h"
#include "playerWait.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerJump.h"
#include "playerStick.h"
#include "playerClimb.h"
#include "playerClimbTop.h"
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

#include "Weapon.h"
//초기??
HRESULT Player::init()
{
	/*====================================================================
		?�래?�어???�브?�트 초기?��? 기본 ?�정???�니??
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wait"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 200));

	//기본 변??초기??
	{
		_obj.ani = new animation;
		_info.jumpPower = 0;
		_info.speed = 4.f;

		_info.hasMember = false;
		_info.hasWeapon = false;
		_info.isImmune = false;
		_info.isAttack = false;
		_info.isHit = false;
		_info.isDead = false;
		_info.isControl = true;
		_info.isConDest = true;
		_info.isSky = false;
		_info.isClimb = false;

		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
		_info.goalState = GOALPOS::PLAYER;

		_info.hp = _info.maxHP = 100;
		_info.force = 10;
		_info.LV = 1;
		_info.exp = 0;
		_info.hitCount = 3;

		_info.frameTimer = TIME_M->getWorldTime();
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		_info.immuneTimer = 0;
	}

	//?�태?�턴 ?�록
	{
		_idle = new playerIdle;
		_wait = new playerWait;
		_walk = new playerWalk;
		_run = new playerRun;
		_jump = new playerJump;
		_stick = new playerStick;
		_climb = new playerClimb;
		_climbTop = new playerClimbTop;
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
	return S_OK;
}

void Player::release()
{
}

//?�뎃 ?�서 중요?�★ ?�태->중력->?�입??
void Player::update()
{
	//cout << (int)_info.state<< endl;

	_obj.prePos = _obj.pos;
	_obj.preShadow = _obj.shadow;

	//?�태?�데?�트
	_IState->UpdateState();

	//중력?�용
	gravity();

	//?�입??
	keyInput();

	
	 hit();
	 //무기 ?�뎃
	if (_info.attackObj!=NULL)weaponUpdate();
	//������ ��ȣ�ۿ�
	checkItem();

	//?�브?�트 ?�뎃
	_obj.update();
	_obj.shadowUpdate();
	
	//?�니 ?�레???�뎃
	if (_info.rendType == RENDERTYPE::ANI_RENDER) _obj.ani->frameUpdate(TIME_M->getElapsedTime() * 7);

	//?�레?�업??
	playFrame();

	if (KEY_M->isOnceKeyDown(VK_NUMPAD0))
	{
		cout << "그림??LT X: " << _obj.shadow.LT.x << endl;
		cout << "그림??LT Y: " << _obj.shadow.LT.y << endl;
		cout << "그림??LT Z: " << _obj.shadow.LT.z << endl;

		cout << "그림??pos X: " << _obj.shadow.pos.x << endl;
		cout << "그림??pos Y: " << _obj.shadow.pos.y << endl;
		cout << "그림??pos Z: " << _obj.shadow.pos.z << endl;

		cout << "캐릭??X: " << _obj.pos.x << endl;
		cout << "캐릭??Y: " << _obj.pos.y << endl;
		cout << "캐릭??Z: " << _obj.pos.z << endl;
		if (_platform != nullptr)
		{
			cout << "?�랫??X: " << _platform->bottomPlane[0].getEnd().x << endl;
			cout << "?�랫??Y: " << _platform->bottomPlane[0].getEnd().y << endl;
			cout << "?�랫??Z: " << _platform->bottomPlane[0].getEnd().z << endl;
		}
		else cout << "NULL" << endl;
		
	}
	
}

//?�더
void Player::render()
{
	/*====================================================================
		Z-ORDER???�라 ?�파 ?�레???�더 ?�킵?�다.
	====================================================================*/

	//?�래?�어 ?�브?�트 ?�더
	ZORDER_M->renderObject(getMapDC(), &_obj, _info.rendType);

	//무기�?가지�??�을 ???�져버렸?�때 ?�져지??무기�??�더)
	if(!_info.hasWeapon)
	{ 
		//?�브?�트참조�??��? ?�았�? ?�더?�태?�면
		if(_info.attackObj != NULL && _info.attackObj->isRender)
		ZORDER_M->renderObject(getMapDC(), _info.attackObj, RENDERTYPE::FRAME_RENDER);
	}

	//?�버�????�트 ?�더
	if (KEY_M->isToggleKey(VK_SHIFT))
	{
		Rectangle(getMapDC(), _obj.shadow.rc);
		if(_info.isAttack) Rectangle(getMapDC(), _info.attackRc);
	}

	}

//?�태 지??
void Player::setState(PL_STATE state)
{
	if (_info.state == state)return;	//같�? ?�태�?변경하지 ?�는??
	_info.preState = _info.state;		//변�????�재 ?�태�??�?�한??
	_info.state = state;				//?�재 ?�태�?변경한??

	//?�태�?빠져?�온??
	if (_IState != NULL) _IState->ExitState();

	//?�태�?변경한??
	switch (_info.state)
	{
		//기본?�작
	case PL_STATE::IDLE:	    _IState = _idle;		 break;
	case PL_STATE::WAIT:	    _IState = _wait;		 break;
	case PL_STATE::WALK:	    _IState = _walk;		 break;
	case PL_STATE::RUN:		    _IState = _run;			 break;
	case PL_STATE::JUMP:		_IState = _jump;		 break;
	case PL_STATE::STICK:	    _IState = _stick;		 break;
	case PL_STATE::CLIMB:      _IState = _climb;		 break;
	case PL_STATE::CLIMBTOP:   _IState = _climbTop;		 break;
	case PL_STATE::PICK:      _IState = _pick;			 break;
		//가??�??�격
	case PL_STATE::GRAB:       _IState = _grab;			 break;
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::ROLL:       _IState = _roll;			 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:		_IState = _stand;		 break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// 공격
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

	//?�태??링크?�고 진입?�다.
	_IState->LinkPlAddress(this);
	_IState->EnterState();
}

//같�? �??�무
bool Player::isRange(GameObject obj)
{
	//?�치 차이가 15미만?�면
	if (abs(_obj.pos.z - obj.pos.z) < 40) return true;
	return false;
}

//같�? �??�무
bool Player::isRange(GameObject obj, float value)
{
	//?�치 차이가 �?미만?�면
	if (abs(_obj.pos.z - obj.pos.z) < value) return true;
	return false;
}

//무기?�뎃
void Player::weaponUpdate()
{
	if (!_info.attackObj) return;

	switch (_info.goalState)
	{
	case GOALPOS::PLAYER:
		break;
	case GOALPOS::WINOUT:
		//골로 ?�동?�다가 ?�면골에 가�?골상?��? 바닥?�로 변�?
		if (moveAttackObj())
		{
			if (_info.dest == DIRECTION::RIGHT) _info.attackGoal.x -= 30;
			if (_info.dest == DIRECTION::LEFT) _info.attackGoal.x += 30;
			_info.attackGoal.y = 0;
			_info.goalState = GOALPOS::FLOOR;
		}
		break;
	case GOALPOS::FLOOR:
		if (moveAttackObj())
		{
			_info.attackObj->isActive = true;
			_info.attackObj->isRender = true;
			_info.goalState = GOALPOS::PLAYER;
			_objectM->pushWeapon(WEAPON_TYPE::BAT, vector3(_info.attackGoal.x, _info.attackGoal.y, _info.attackGoal.z));
			_info.attackObj = NULL;
		}
		break;
	}
}

bool Player::moveAttackObj()
{
	_info.attackObj->pos.x += cosf(getAngle(_info.attackObj->pos.x, 0,  _info.attackGoal.x, 0)) * 6.0f;
	
	_info.attackObj->pos.z -= sinf(getAngle( 0 ,_info.attackObj->pos.z, 0 , _info.attackGoal.z)) * 6.0f;

	_info.attackObj->pos.y -= sinf(getAngle(0, _info.attackObj->pos.y, 0, _info.attackGoal.y)) * 6.0f;
	
	//공격 ?�트 ?�성
	_info.attackRc = RectMakeCenter(_info.attackObj->pos.x,
		_info.attackObj->pos.z + _info.attackObj->pos.y,
		_info.attackObj->size.x + 200, _info.attackObj->size.z + 100);

	if (getDistance(_info.attackObj->pos.x, _info.attackObj->pos.z + _info.attackObj->pos.y,
		_info.attackGoal.x, _info.attackGoal.z + _info.attackGoal.y) < 5)
	{
		_info.attackObj->pos.x = _info.attackGoal.x;
		_info.attackObj->pos.y = _info.attackGoal.y;
		_info.attackObj->pos.z = _info.attackGoal.z;
		return true;
	}
	return false;
}

void Player::hit()
{
	//?��? ?�태가 ?�니�??�?�머 초기??
	if (!_info.isImmune)
	_info.immuneTimer = TIME_M->getWorldTime();

	//?��? ?�태�?4초�? 지?�다�??��? ?�남
	 if (_info.isImmune && TIME_M->getWorldTime() - _info.immuneTimer > 4.f)
	{
		_info.isImmune = false;
		_obj.alpha = 255;
	}

	 //?��? 0?�하가 ?�면
	 if (_info.hp <= 0)setState(PL_STATE::DEAD);

	//Dead ?�태가 ?�니�??��????�니�??�턴 ?�태가 ?�니�?
	if (_info.state != PL_STATE::DEAD && !_info.isImmune && _info.state != PL_STATE::STUN)
	{
		//가???�태가 ?�니�?
		if (_info.state != PL_STATE::GUARD)
		{
			for (int i = 0; i != _enemyM->getVEnemy().size(); i++)
			{
				if (_enemyM->getVEnemy()[i]->getInfo().isAttack)
				{
					RECT temp;
					if (IntersectRect(&temp, &_obj.rc, &_enemyM->getVEnemy()[i]->getInfo().rcAttack)
						&& isRange(_enemyM->getVEnemy()[i]->getRefObj()))
					{
						if (_info.hitCount >= 4)
						{ 
							//?��? 10 ?�하�??�턴 / 10 초과�??�운 ?�태
							_info.hitCount = 0;
							if(_info.hp<=10)setState(PL_STATE::STUN);
							if (_info.hp > 10)setState(PL_STATE::DOWN); 
						}
						else setState(PL_STATE::HIT);
					}
				}
			}
			

		}

	}
}


//?�테?��?가 바�??�마??초기?�시?�는 ?�수
void Player::stageInit()
{
	/*====================================================================
		?�테?��?가 바�??�마??초기?�시?�는 ?�수?�니??
	====================================================================*/
	switch (_stageM->getCurStage()) // ?�재 ?�테?��???
	{
	case STAGETYPE::EASY: // ?�재 ?�테?��?가 ?��?�?
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // ?�전 ?�테?��?가 ?�말?��??�면
		{
			_obj.setPosX(1445);
			_obj.setPosY(0);
			_obj.setPosZ(420);
		}
		break;
	case STAGETYPE::NORMAL:  // ?�재 ?�테?��?가 ?�말?�면
		if (_stageM->getPreStage() == STAGETYPE::EASY) // ?�전 ?�테?��?가 ?�말?��??�면
		{
			_obj.setPosX(180);
			_obj.setPosY(0);
			_obj.setPosZ(700);
		}
		else if (_stageM->getPreStage() == STAGETYPE::HARD) // ?�전 ?�테?��?가 ?�드?��??�면
		{
			_obj.setPosX(2645);
			_obj.setPosY(0);
			_obj.setPosZ(670);
		}
		break;
	case STAGETYPE::HARD: // ?�재 ?�테?��?가 ?�드�?
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // ?�전 ?�테?��?가 ?�말?��??�면
		{
			_obj.setPosX(270);
			_obj.setPosY(0); 
			_obj.setPosZ(480);
		}
		else if (_stageM->getPreStage() == STAGETYPE::BOSS) // ?�전 ?�테?��?가 보스?�?�면
		{
			_obj.setPosX(2070);
			_obj.setPosY(0);
			_obj.setPosZ(1370);
		}
		break;
	case STAGETYPE::BOSS: // ?�재 ?�테?��?가 보스�?
		if (_stageM->getPreStage() == STAGETYPE::HARD) // ?�전 ?�테?��?가 ?�드?��??�면
		{
			_obj.setPosX(275);
			_obj.setPosY(0);
			_obj.setPosZ(605);
		}
		break;
	default:
		break;
	}

	/*====================================================================
		링크 : ?�너미매?��?, ?�브?�트 매니?�?� 링크?�니??
	====================================================================*/
	_enemyM = _stageM->getStage()->getEnemyM();
	_objectM = _stageM->getStage()->getObjectM();
}

//?��?지 변�?
void Player::changeImg(string imgName, bool reverse)
{
	//?��?지�?바꾼??
	_obj.img = IMG_M->findImage(imgName);

	//방향�?리버???��? ?�른 ?�레??x ?�덱???�정
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		if (!reverse)_obj.imgIndex.x = 0;
		else if (reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX();
		_obj.imgIndex.y = 0;
		break;

	case DIRECTION::RIGHT:
		if (!reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX();
		else if (reverse)_obj.imgIndex.x = 0;
		_obj.imgIndex.y = 1;
		break;
	}

	//?�레???�간 갱신?�여 바로 ?�레??변�?
	_info.frameTimer = TIME_M->getWorldTime();

}

//?�레???�산
void Player::setFrame(FRAMETYPE frameType, float frameInterval)
{
	//?�레??y 번호 ?�정
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}
	if (_info.state == PL_STATE::CLIMB || _info.state == PL_STATE::CLIMBTOP)
		_obj.imgIndex.y = 0;
	//?�레??y 번호 ?�팅
	_obj.img->setFrameY((int)_info.dest);

	//?�레???�행 ?�간 ?�정
	if (TIME_M->getWorldTime() - _info.frameTimer > frameInterval)
	{
		//?�간 갱신
		_info.frameTimer = TIME_M->getWorldTime();
		switch (_info.dest)
		{
		case DIRECTION::LEFT:
			if (frameType != FRAMETYPE::REVERSELOOP && frameType != FRAMETYPE::REVERSEONCE) ++_obj.imgIndex.x;
			else --_obj.imgIndex.x;


			break;
		case DIRECTION::RIGHT:
			if (frameType != FRAMETYPE::REVERSELOOP&& frameType != FRAMETYPE::REVERSEONCE) --_obj.imgIndex.x;
			else  ++_obj.imgIndex.x;
			break;
		}
	}

	//?�레??x 번호 조절
	switch (frameType)
	{
	case FRAMETYPE::ONCE://??�??�생
	{
		//?�쪽??경우 x?�덱?��? 0번�??? ?�번까�? ?�레?�이 ???�면 ?�번?�로 ?�레?�번??고정
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
		//?�른쪽의 경우 x?�덱?��? ?�번부??0번까지 ?�레?�이 ???�면 0번으�??�레??번호 고정
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0;
		}

	}
	break;
	case FRAMETYPE::LOOP://무한 ?�생
	{
		//?�쪽??경우 x?�덱?��? 0번�??? ?�번까�? ?�레?�이 ???�면 ?�번?�로 ?�레?�번??0번으�?갱신
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		//?�른쪽의 경우 x?�덱?��? ?�번부??0번까지 ?�레?�이 ???�면 0번으�??�레??번호 ?�번?�로 갱신
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
	}
	break;
	case FRAMETYPE::REVERSEONCE://반�? ?�번 ?�생
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0; return;
		}
	}
	break;
	case FRAMETYPE::REVERSELOOP://반�? 무한 ?�생
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();

	}
	break;
	}

}

//?�레???�행
void Player::playFrame()
{
	switch (_info.state)
	{
		//무한?�생 (?�반 ?�도)
	case PL_STATE::WAIT:

		setFrame(FRAMETYPE::LOOP, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//반�? 무한?�생 (빨리)
	case PL_STATE::RUN:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL*0.35);
		break;
		//반�? 무한?�생
	case PL_STATE::STUN:
	case PL_STATE::IDLE:	case PL_STATE::WALK:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL);
		break;

		//?�번 (천천??
	case PL_STATE::PICK:	case PL_STATE::GRAB:
	case PL_STATE::STICK:	case PL_STATE::HIT:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 3);
	case PL_STATE::CLIMBTOP:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 5);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//?�번 (?�반 ?�도)
	case PL_STATE::JUMP:
	case PL_STATE::ROLL:
	case PL_STATE::STAND:
	case PL_STATE::DOWN:	case PL_STATE::DEAD:
	case PL_STATE::THROW:
	case PL_STATE::COMBO1:	case PL_STATE::COMBO2:
	case PL_STATE::COMBO3:	case PL_STATE::SATTACK:
	case PL_STATE::DASHSATTACK:
	case PL_STATE::JUMPATTACK:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//반�? ?�번?�생 (?�반 ?�도)
	case PL_STATE::STOMP:
	case PL_STATE::DASHATTACK:	case PL_STATE::SATTACKDOWN:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//반�? ?�번?�생 (빨리)
	case PL_STATE::GUARD:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL*0.4);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//?�니?�더
	case PL_STATE::CLIMB:
		_info.rendType = RENDERTYPE::ANI_RENDER;
		_obj.ani->setFPS(1);
		break;
	}

}

//좌표?�동
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//그림?�만 ?�단 ?�번 ?�데?�트 (충돌처리�??�한 �? 건드리면 ?�됨!)
	_obj.shadowUpdate();

	//충돌처리
	_colM->playerObjectCollision();

	//그림???�래�????�어지?�록 ?�외처리
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//최종 ?�트 갱신
	_obj.update();
}

//좌표?�정
void Player::setPos(float x, float z, float y)
{
	_obj.pos.x = x;
	_obj.pos.z = z;
	_obj.pos.y = y;

	//그림?�만 ?�단 ?�번 ?�데?�트 (충돌처리�??�한�? 건드리면 ?�됨!)
	_obj.shadowUpdate();

	//충돌처리
	_colM->playerObjectCollision();

	//그림???�래�????�어지?�록 ?�외처리
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//최종 ?�트 갱신
	_obj.update();
}

//�������̶� ��ȣ�ۿ�
void Player::checkItem()
{
	RECT temp;
	for (int i = 0; i != _objectM->getVObject().size();i++)
	{
		//Ȱ��ȭ �����϶�
		if (_objectM->getVObject()[i]->getObj()->isActive)
		{
			// �浹�Ѵٸ�
			if (IntersectRect(&temp, &_obj.rc, &_objectM->getVObject()[i]->getRefObj().rc))
			{
				switch (_objectM->getVObject()[i]->getInfo().type)
				{
				//������ �÷���
				case ITEM_TYPE::MONEY:
					break;
				case ITEM_TYPE::COIN:
					break;
				//ü��ȸ��
				case ITEM_TYPE::MEAT:
				case ITEM_TYPE::APPLE:
				case ITEM_TYPE::HEN:
				case ITEM_TYPE::CHILI:
					if (_info.hp < _info.maxHP)
					{
						_info.hp += _objectM->getVObject()[i]->getInfo().healValue;
						_objectM->popObject(i);
						if (i == _objectM->getVObject().size())return;
					}
					break;
				}
			}
			
		}
	}

	//ü�¼�ġ ����
	if (_info.hp > _info.maxHP)
	{
		_info.hp = _info.maxHP;
	}
}


//중력?�용
void Player::gravity()
{
	if (_info.isSky) _info.jumpPower -= GRAVITY;
	if (_obj.pos.y >= 0 && _info.isSky)
	{
		setState(PL_STATE::IDLE);
		//걷거???�고?�었�? ?��? 계속 ?�르고있?�면 �??�태 그�?로돌?�오�?
		if (_info.preState == PL_STATE::WALK || _info.preState == PL_STATE::RUN)
		{
			if (_info.dest == DIRECTION::LEFT && KEY_M->isStayKeyDown(VK_LEFT))setState(_info.preState);
			if (_info.dest == DIRECTION::RIGHT && KEY_M->isStayKeyDown(VK_RIGHT))setState(_info.preState);
		}
		_info.isSky = false;
		_platform = nullptr;
	}
	if (_obj.pos.y > 0) _info.jumpPower = 0;
	movePos(0, 0, _info.jumpPower);
}

//?�입??
void Player::keyInput()
{
	//?�조?�을 못하???�태?�면 리턴
	if (!_info.isControl) return;

	//공격?�받�?커맨?��??�해)
	if (KEY_M->isOnceKeyDownV('D'));

	//?�다리오르기
	if (_info.isClimb && (GetAsyncKeyState(VK_UP) & 0x8000)) setState(PL_STATE::CLIMB);

	//?�프
	if (KEY_M->isOnceKeyDownV('A') && !_info.isSky)
	{
		//?�전?�태 ?�??
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWER;
		movePos(0, 0, JUMPPOWER);
		//?�프?�워가 - �??�프?�태�??�환
		if (_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
	}
	//구르�?
	if (KEY_M->isOnceKeyDownV('W') && !_info.isSky)
	{
		//?�전?�태 ?�??
		_info.preState = _info.state;
		setState(PL_STATE::ROLL);
	}

	//방향조작??못하???�태?�면 리턴
	if (!_info.isConDest) return;

	//??
	if (KEY_M->isOnceKeyDownV(VK_LEFT) || KEY_M->isStayKeyDown(VK_LEFT))
	{
		_info.moveDest = MOVE_DIRECTION::LEFT;
		_info.dest = DIRECTION::LEFT;
	}
	//??
	if (KEY_M->isOnceKeyDownV(VK_RIGHT) || KEY_M->isStayKeyDown(VK_RIGHT))
	{
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
	}
	//??
	if (KEY_M->isOnceKeyDownV(VK_UP) || KEY_M->isStayKeyDown(VK_UP))_info.moveDest = MOVE_DIRECTION::UP;
	//?�래
	if (KEY_M->isOnceKeyDownV(VK_DOWN) || KEY_M->isStayKeyDown(VK_DOWN))_info.moveDest = MOVE_DIRECTION::DOWN;


	//?�커맨드
	if (!_info.isSky && KEY_M->getVKeyBuffer().size() >= 3)
	{
		//바라보는 방향?? ??+ d 커맨??공격
		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_RIGHT && _info.dest == DIRECTION::RIGHT)
			setState(PL_STATE::SATTACKDOWN);

		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_LEFT && _info.dest == DIRECTION::LEFT)
			setState(PL_STATE::SATTACKDOWN);

	}
}
