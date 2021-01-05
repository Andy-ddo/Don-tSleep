#include "stdafx.h"
#include "GameObject.h"

//�ʱ�ȭ (�׷�, �̹���, ��ġ)
void GameObject::init(OBJECT_GROUP _group, image* _img, vector3 _pos)
{
	img = _img;
	group = _group;

	pos = _pos;
	zAngle = - PI / 4;
	size.x = img->getFrameWidth();
	size.z = img->getFrameHeight();

	alpha = 255;

	RectRenew();

	switch (group)
	{
	case OBJECT_GROUP::PLAYER:
		isShadow = true;
		break;
	case OBJECT_GROUP::ENEMY:
		isShadow = true;
		break;
	case OBJECT_GROUP::BOSS:
		isShadow = true;
		break;
	case OBJECT_GROUP::OBJECT:
		isShadow = false;
		break;
	case OBJECT_GROUP::ITEM:
		isShadow = false;
		break;
	default:
		break;
	}

	isActive = true;
}

void GameObject::init(OBJECT_GROUP _group, image* _img, vector3 _pos, float a)
{
	img = _img;
	group = _group;

	pos = _pos;
	margin = a;
	zAngle = -PI / 4;
	size.x = img->getFrameWidth();
	size.z = img->getFrameHeight();

	alpha = 255;

	RectRenew();

	switch (group)
	{
	case OBJECT_GROUP::PLAYER:
		isShadow = true;
		break;
	case OBJECT_GROUP::ENEMY:
		isShadow = true;
		break;
	case OBJECT_GROUP::BOSS:
		isShadow = true;
		break;
	case OBJECT_GROUP::OBJECT:
		topPlane[0] = Linear(vector3(pos.x - size.x / 2 + margin, -size.z + margin, pos.z - size.z), vector3(pos.x + size.x / 2, -size.z + margin, pos.z - size.z));					// ���� ����
		topPlane[1] = Linear(vector3(pos.x + size.x / 2, -size.z + margin, pos.z - size.z), vector3(pos.x + size.x / 2 - margin, -size.z + margin, pos.z - size.z + margin));			// ������ ����
		topPlane[2] = Linear(vector3(pos.x + size.x / 2 - margin, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - size.x / 2, -size.z + margin, pos.z - size.z + margin)); // ���� ����
		topPlane[3] = Linear(vector3(pos.x - size.x / 2, -size.z + margin, pos.z - size.z + margin), vector3(pos.x - size.x / 2 + margin, -size.z + margin, pos.z - size.z));			// ���� ����

		bottomPlane[0] = Linear(vector3(pos.x - size.x / 2 + margin, (float)0, pos.z - margin), vector3(pos.x + size.x / 2, (float)0, pos.z - margin));			// ���� ����
		bottomPlane[1] = Linear(vector3(pos.x + size.x / 2, (float)0, pos.z - margin), vector3(pos.x + size.x / 2 - margin, (float)0, pos.z));					// ������ ����
		bottomPlane[2] = Linear(vector3(pos.x + size.x / 2 - margin, (float)0, pos.z), vector3(pos.x - size.x / 2, (float)0, pos.z));							// ���� ����
		bottomPlane[3] = Linear(vector3(pos.x - size.x / 2, (float)0, pos.z), vector3(pos.x - size.x / 2 + margin, (float)0, pos.z - margin));					// ���� ����

		// �׸��� ���� ���е�, �浹ó�������� �Ⱦ�����
		sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
		sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
		sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
		sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());

	case OBJECT_GROUP::ITEM:
		isShadow = false;
		break;
	default:
		break;
	}

/*====================================================================
					�׸��� �� �浹 ó���� ���� �� �����մϴ�.
====================================================================*/
	if (isShadow)
	{
		shadow.pos = vector3(pos.x, pos.y, pos.z);
		shadow.LT = vector3(pos.x - size.x / 2, pos.y, pos.z - 10);
		shadow.RT = vector3(pos.x + size.x / 2, pos.y, pos.z - 10);
		shadow.RB = vector3(pos.x + size.x / 2, pos.y, pos.z + 10);
		shadow.LB = vector3(pos.x - size.x / 2, pos.y, pos.z + 10);
		shadow.rc = RectMakeCenter(pos.x, pos.z, size.x, 20);
	}

	isActive = true;
}

void GameObject::release()
{

}

void GameObject::update()
{
	size.x = img->getFrameWidth();
	size.z = img->getFrameHeight();
	RectRenew();
	shadowUpdate();
}

void GameObject::render()
{

}

void GameObject::RectRenew()
{
	rc = RectMakeCenter(pos.x, pos.z - size.z / 2 + pos.y, size.x, size.z);
}

void GameObject::shadowUpdate()
{
/*====================================================================
					�׸��� ������Ʈ
====================================================================*/
	shadow.pos = vector3(pos.x, pos.y, pos.z);
	shadow.LT = vector3(pos.x - size.x / 2, pos.y, pos.z - 10);
	shadow.RT = vector3(pos.x + size.x / 2, pos.y, pos.z - 10);
	shadow.RB = vector3(pos.x + size.x / 2, pos.y, pos.z + 10);
	shadow.LB = vector3(pos.x - size.x / 2, pos.y, pos.z + 10);
	shadow.rc = RectMakeCenter(pos.x, pos.z, size.x, 20);
}

void GameObject::PolyLineRender(HDC hdc)
{
	if (KEY_M->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 4; ++i)
		{
			topPlane[i].LinearRender(hdc);
			bottomPlane[i].LinearRender(hdc);
			sideHeight[i].LinearRender(hdc);
		}
	}
}
