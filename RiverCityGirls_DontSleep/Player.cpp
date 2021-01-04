#include "stdafx.h"
#include "Player.h"

#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

HRESULT Player::init()
{
	/*====================================================================
		�÷��̾��� ������Ʈ �ʱ�ȭ�� �⺻ ������ �մϴ�.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("kyoko"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2));
	_obj.imgIndex = { 0,0 };	//���� �ִϸ��̼��� ��������� �ʾ� �ӽ÷� �صξ����ϴ�.

	_speed = SPEED;
	_jumpCount = 1;
	_isControl = true;

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

void Player::update()
{
	keyInput();
	move();
	shadowUpdate();
	_obj.update();
	playerObjectCollision();
	shadowUpdate();
	_obj.update();
}

void Player::render()
{
	/*====================================================================
		Z-ORDER�� ���� ���� ������ ���� ��ŵ�ϴ�.
	====================================================================*/
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
	//(���� �÷��̾� �ִϸ��̼��� ���� �ӽ÷� �صξ����ϴ�. ���߿� ANI_RENDER�� �ٲ㼭 ������!)
}

void Player::move()
{
	_obj.prePos = _obj.pos;
	_obj.pos.y -= _jumpPower;
	if (_obj.pos.y > _jumpPower)_jumpPower = 0;
	if (_obj.pos.y < 0) _jumpPower -= GRAVITY;

	if (_jumpPower == 0) _jumpCount = 1;
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

void Player::keyInput()
{
	if (!_isControl) return;		//��Ʈ���� �Ұ����ϸ� �����Ѵ�.

	if (KEY_M->isOnceKeyDown(VK_SPACE) && _jumpPower <= 0 && _jumpCount > 0)
	{
		_jumpPower = JUMPPOWER;
		_jumpCount--;
	}

	if (KEY_M->isStayKeyDown(VK_UP))
	{
		_obj.pos.z -= _speed;
	}
	if (KEY_M->isStayKeyDown(VK_DOWN))
	{
		_obj.pos.z += _speed;
	}

	if (KEY_M->isStayKeyDown(VK_RIGHT))
	{
		_obj.pos.x += _speed;
	}

	if (KEY_M->isStayKeyDown(VK_LEFT))
	{
		_obj.pos.x -= _speed;
	}
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
					_jumpPower = 0;
					_jumpCount = 0;
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
