#include "stdafx.h"
#include "Player.h"
//�ܺ�
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
//����
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

//�ʱ�ȭ
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
		_info._frameTimer = TIME_M->getWorldTime();

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

	////////////////////////////////////////��� ����ؾ���? �������
	//move();
	shadowUpdate();
	_obj.update(); //����ϳ�
	playerObjectCollision();
	shadowUpdate();
	_obj.update(); //�̰� �� �ΰ�..? 
}

void Player::render()
{
	/*====================================================================
		Z-ORDER�� ���� ���� ������ ���� ��ŵ�ϴ�.
	====================================================================*/
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
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

void Player::shadowUpdate()
{
	_shadow.pos = vector3(_obj.pos.x, _obj.pos.y, _obj.pos.z);
	_shadow.rc = RectMakeCenter(_shadow.pos.x, _shadow.pos.z, _obj.img->getWidth(), 20);
	_shadow.LT = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RT = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RB = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z + 10);
	_shadow.LB = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z + 10);
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
void Player::changeImg(string imgName)
{
	//�̹����� �ٲ۴�.
	_obj.img = IMG_M->findImage(imgName);
	//������ �ð� ����
	_info._frameTimer = TIME_M->getWorldTime();
	//���⿡ ���� �̹����� x,y���� ����
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.x = 0;
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.x = _obj.img->getMaxFrameX();
		_obj.imgIndex.y = 1;
		break;
	}
	//������ ���� ��� ����


	//���⸻�� �����ӷ������־����
	_obj.img->setFrameY((int)_obj.imgIndex.y);
	if (_info.dest == DIRECTION::LEFT) _obj.img->setFrameX(0);
	else if (_info.dest == DIRECTION::RIGHT) _obj.img->setFrameX(_obj.img->getMaxFrameX());

}

//������ ���
void Player::playFrame()
{
}

//��ǥ�̵�
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//�׸��� �Ʒ��� �� ���������� ����ó��
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//��Ʈ����
	_obj.RectRenew();
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
	if (KEY_M->isOnceKeyDownV('A'))// <<��� �ٵǿ� �Ф�
	{
		//�������� ����
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWERVALUE;
		movePos(0, 0, JUMPPOWERVALUE);
	//�����Ŀ��� - �� �������·� ��ȯ
	if(_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
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


void Player::move()
{
	_obj.prePos = _obj.pos;

	_obj.pos.y -= _info.jumpPower;
	if (_obj.pos.y > _info.jumpPower)_info.jumpPower = 0;
	if (_obj.pos.y < 0) _info.jumpPower -= GRAVITY;

	if (_info.jumpPower == 0) _info.isSky = true;
}
void Player::playerObjectCollision()
{
	for (int i = 0; i < _objectM->getVObject().size(); ++i)
	{
		GameObject* obs = _objectM->getVObject()[i]->getObj();
		if (obs->group == OBJECT_GROUP::OBJECT)
		{
			AirCollision(&_obj, &_shadow, obs);
		}
	}
}
void Player::LRUDCollision(GameObject* cha, tagShadow* sh, GameObject* obj)
{
	if (obj->group == OBJECT_GROUP::OBJECT)
	{
		vector3 interVector; // �������� ���� ����
		if (cha->prePos.x < cha->pos.x && cha->prePos.z == cha->pos.z) // �÷��̾ ���������� �������� ��
		{
			if (obj->bottomPlane[3].getEnd().z < sh->RB.z &&
				sh->RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (Linear(sh->RT, sh->RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // ���� ������ �������̶� �����ϸ�
					Linear(sh->RT, sh->RB).segmentIntersect(obj->bottomPlane[2], &interVector))	// ���� ������ �غ��̶� �����ϸ�
				{
					if (sh->RB.z < obj->bottomPlane[3].getStart().z) // �׸��� �غ��� ������Ʈ �غ����� ���� ���� ���
					{
						cha->pos.x = obj->bottomPlane[3].getX(sh->RB.z) - cha->size.x / 2; // ���� ������ �������� ����
					}
					else // �׸��� �غ��� ������Ʈ �غ����� �Ʒ��� ���� ���
					{
						cha->pos.x = obj->bottomPlane[3].getStart().x - cha->size.x / 2;
					}
				}
			}
		}
		else if (cha->pos.x < cha->prePos.x && cha->prePos.z == cha->pos.z) // �÷��̾ �������� �������� ��
		{
			if (obj->bottomPlane[1].getStart().z < sh->LB.z &&
				sh->LT.z < obj->bottomPlane[1].getEnd().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (Linear(sh->LT, sh->LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // ���� ������ �������̶� ������
					Linear(sh->LT, sh->LB).segmentIntersect(obj->bottomPlane[0], &interVector))    // ���� ������ ���غ��̶� �����ϸ�
				{
					if (obj->bottomPlane[1].getStart().z < sh->LT.z) // �׸��� ������ ������Ʈ �������� �Ʒ��� ���� ���
					{
						cha->pos.x = obj->bottomPlane[1].getX(sh->LT.z) + cha->size.x / 2; // ���� ������ �������� ����
					}
					else // �׸��� ������ ������Ʈ �������� ���� ���� ���
					{
						cha->pos.x = obj->bottomPlane[1].getStart().x + cha->size.x / 2;
					}

				}
			}
		}
		if (cha->prePos.z < cha->pos.z) // �÷��̾ �Ʒ��� �������� ��
		{
			if (obj->bottomPlane[0].getStart().x < sh->RB.x &&
				sh->LB.x < obj->bottomPlane[0].getEnd().x) // ������Ʈ�� x ���� �ȿ� ������ ��
			{
				if (sh->LT.z < obj->bottomPlane[0].getStart().z &&
					obj->bottomPlane[0].getStart().z < sh->LB.z) // �غ��� ������Ʈ�� ������ �Ѿ��
				{
					cha->pos.z = obj->bottomPlane[0].getStart().z - 10;
				}
			}
			else if (obj->bottomPlane[3].getEnd().z < sh->RB.z &&
				sh->RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (Linear(sh->LB, sh->RB).segmentIntersect(obj->bottomPlane[3], &interVector) ||
					Linear(sh->LT, sh->RT).segmentIntersect(obj->bottomPlane[3], &interVector)) // �غ� ������ �������̶� �����ϸ�
				{
					if (interVector.x < sh->RB.x)
					{
						cha->pos.x = interVector.x - cha->size.x / 2; // ���� ������ �������� ����
					}
				}
			}
		}
		else if (cha->pos.z < cha->prePos.z) // �÷��̾ �������� �������� ��
		{
			if (obj->bottomPlane[2].getEnd().x < sh->RT.x &&
				sh->LT.x < obj->bottomPlane[2].getStart().x) // ������Ʈ�� x ���� �ȿ� ������ ��
			{
				if (sh->RT.z < obj->bottomPlane[2].getEnd().z &&
					obj->bottomPlane[2].getEnd().z < sh->RB.z) // ������ ������Ʈ�� �ظ��� �Ѿ��
				{
					cha->pos.z = obj->bottomPlane[2].getEnd().z + 10;
				}
			}
			else if (obj->bottomPlane[3].getEnd().z < sh->RB.z &&
				sh->RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (Linear(sh->LT, sh->RT).segmentIntersect(obj->bottomPlane[1], &interVector) ||
					Linear(sh->LB, sh->RB).segmentIntersect(obj->bottomPlane[1], &interVector)) // ���� ������ �����ϸ�
				{
					if (sh->LT.x < interVector.x)
					{
						cha->pos.x = interVector.x + cha->size.x / 2; // ���� ������ ���������� ����
					}
				}
			}
		}
	}
}
void Player::AirCollision(GameObject* cha, tagShadow* sh, GameObject * obj)
{
	if (cha->prePos.y < cha->pos.y) // ���� ���� ��
	{
		if (obj->bottomPlane[0].getStart().z < sh->LB.z &&			// ĳ������ z���� �������� �ؿ� �ְ�
			sh->LT.z < obj->bottomPlane[2].getStart().z &&			// ĳ������ z���� �غ����� ���� �ְ�
			obj->bottomPlane[3].getX(sh->RB.z) < sh->RB.x &&			// ĳ������ x���� ���������� ������ �ְ�
			sh->LB.x < obj->bottomPlane[1].getX(sh->LT.z))			// ĳ������ x���� ���������� ������ �ְ�
		{
			if (cha->prePos.y <= obj->topPlane[0].getStart().y)			// ���� y���� ������Ʈ ���� ������ ũ��
			{
				if (obj->topPlane[0].getStart().y < cha->pos.y)			// ������Ʈ ���� ��������
				{
					cha->pos.y = obj->topPlane[0].getStart().y;
					_info.jumpPower = 0;
					_info.isSky = false;
				}
			}
			else
			{
				LRUDCollision(cha, sh, obj);
			}
		}

	}
	else if (cha->pos.y < cha->prePos.y) // ���� ���� ��
	{
		if (obj->topPlane[0].getStart().y < cha->pos.y) // ������Ʈ ���̺��� ���� ��
		{
			LRUDCollision(cha, sh, obj);
		}
	}
	else // �׳� ���鿡 ���� ��
	{
		LRUDCollision(cha, sh, obj);

	}
}







