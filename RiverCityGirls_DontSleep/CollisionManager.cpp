#include "stdafx.h"
#include "CollisionManager.h"

#include "StageManager.h"
#include "Stage.h"
#include "Player.h"

HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}

void CollisionManager::LRUDCollision(GameObject* character, GameObject* obj)
{
	vector3 interVector; // �������� ���� ����
	if (character->prePos.z < character->pos.z) // �÷��̾ �Ʒ��� �������� ��
	{
		if (obj->bottomPlane[0].getStart().x < character->shadow.RB.x &&
			character->shadow.LB.x < obj->bottomPlane[0].getEnd().x) // ������Ʈ�� x ���� �ȿ� ������ ��
		{
			if (character->shadow.LT.z < obj->bottomPlane[0].getStart().z &&
				obj->bottomPlane[0].getStart().z < character->shadow.LB.z) // �غ��� ������Ʈ�� ������ �Ѿ��
			{
				character->pos.z = obj->bottomPlane[0].getStart().z - 10;
			}
		}
		else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
			character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
		{
			if (Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) ||
				Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[3], &interVector)) // �غ� ������ �������̶� �����ϸ�
			{
				if (interVector.x < character->shadow.RB.x)
				{
					character->pos.x = interVector.x - character->size.x / 2; // ���� ������ �������� ����
				}
			}
		}
	}
	else if (character->prePos.z > character->pos.z) // �÷��̾ �������� �������� ��
	{
		if (obj->bottomPlane[2].getEnd().x < character->shadow.RT.x &&
			character->shadow.LT.x < obj->bottomPlane[2].getStart().x) // ������Ʈ�� x ���� �ȿ� ������ ��
		{
			if (character->shadow.RT.z < obj->bottomPlane[2].getEnd().z &&
				obj->bottomPlane[2].getEnd().z < character->shadow.RB.z) // ������ ������Ʈ�� �ظ��� �Ѿ��
			{
				character->pos.z = obj->bottomPlane[2].getEnd().z + 10;
			}
		}
		else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
			character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
		{
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector) ||
				Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector)) // ���� ������ �����ϸ�
			{
				if (character->shadow.LT.x < interVector.x)
				{
					character->pos.x = interVector.x + character->size.x / 2; // ���� ������ ���������� ����
				}
			}
		}
	}
	if (character->prePos.x < character->pos.x && character->prePos.z == character->pos.z) // �÷��̾ ���������� �������� ��
	{
		if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
			character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
		{
			if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // ���� ������ �������̶� �����ϸ�
				Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[2], &interVector))	// ���� ������ �غ��̶� �����ϸ�
			{
				if (character->shadow.RB.z < obj->bottomPlane[3].getStart().z) // �׸��� �غ��� ������Ʈ �غ����� ���� ���� ���
				{
					character->pos.x = obj->bottomPlane[3].getX(character->shadow.RB.z) - character->size.x / 2; // ���� ������ �������� ����
				}
				else // �׸��� �غ��� ������Ʈ �غ����� �Ʒ��� ���� ���
				{
					character->pos.x = obj->bottomPlane[3].getStart().x - character->size.x / 2;
				}
			}
		}
	}
	else if (character->prePos.x > character->pos.x && character->prePos.z == character->pos.z) // �÷��̾ �������� �������� ��
	{
		if (obj->bottomPlane[1].getStart().z < character->shadow.LB.z &&
			character->shadow.LT.z < obj->bottomPlane[1].getEnd().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
		{
			if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // ���� ������ �������̶� ������
				Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[0], &interVector))    // ���� ������ �����̶� �����ϸ�
			{
				if (obj->bottomPlane[1].getStart().z < character->shadow.LT.z) // �׸��� ������ ������Ʈ �������� �Ʒ��� ���� ���
				{
					character->pos.x = obj->bottomPlane[1].getX(character->shadow.LT.z) + character->size.x / 2; // ���� ������ �������� ����
				}
				else // �׸��� ������ ������Ʈ �������� ���� ���� ���
				{
					character->pos.x = obj->bottomPlane[1].getStart().x + character->size.x / 2;
				}
			}
		}
	}

}

void CollisionManager::objectCollision()
{
	wallCollsion();
	GameObject* character = _stageM->getPlayer()->getPObj();
	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();
	for (int i = 0; i < vObj.size(); ++i)
	{
		GameObject* obj = vObj[i]->getObj();
		if (obj->group == OBJECT_GROUP::OBJECT)
		{
			if (character->prePos.y < character->pos.y) // ���� ���� ��
			{
				if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&			// ĳ������ z���� �������� �ؿ� �ְ�
					character->shadow.LT.z < obj->bottomPlane[2].getStart().z &&			// ĳ������ z���� �غ����� ���� �ְ�
					obj->bottomPlane[3].getX(character->shadow.RB.z) < character->shadow.RB.x &&			// ĳ������ x���� ���������� ������ �ְ�
					character->shadow.LB.x < obj->bottomPlane[1].getX(character->shadow.LT.z))			// ĳ������ x���� ���������� ������ �ְ�
				{
					if (character->prePos.y <= obj->topPlane[0].getStart().y)			// ���� y���� ������Ʈ ���� ������ ũ��
					{
						if (obj->topPlane[0].getStart().y < character->pos.y)			// ������Ʈ ���� ��������
						{
							character->pos.y = obj->topPlane[0].getStart().y;
						}
					}
					else
					{
						LRUDCollision(character, obj);
					}
				}
			}
			else if (character->pos.y < character->prePos.y) // ���� ���� ��
			{
				if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ���� ��
				{
					LRUDCollision(character, obj);
				}
			}
			else // �׳� ���鿡 ���� ��
			{
				LRUDCollision(character, obj);
			}
		}
	}
}

void CollisionManager::wallCollsion()
{
	GameObject* character = _stageM->getPlayer()->getPObj();
	tagWall leftWall = _stageM->getStage()->getLeftWall();
	tagWall rightWall = _stageM->getStage()->getRightWall();
	tagWall backWall = _stageM->getStage()->getBackWall();
	tagWall floor = _stageM->getStage()->getFloor();
	vector3 interVector;

	if (character->shadow.LT.z < backWall.LB.z)
	{
		character->pos.z = backWall.LB.z + 10;
	}
	else if (character->shadow.LB.z > floor.LB.z)
	{
		character->pos.z = floor.LB.z - 10;
	}

	if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(leftWall.RB, leftWall.LB), &interVector))  // �׸��� ������ ���� ���̶� �����ϸ�
	{
		character->pos.x = interVector.x + character->size.x / 2;
	}
	if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(rightWall.LB, rightWall.RB), &interVector))  // �׸��� ������ ������ ���̶� �����ϸ�
	{
		character->pos.x = interVector.x - character->size.x / 2;
	}

	

}
