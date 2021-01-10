#include "stdafx.h"
#include "HardStage.h"

HRESULT HardStage::init()
{
	Stage::init();
	/*====================================================================
		���������� ��� �̹����� �����ϰ�, ī�޶󿡰� �� ����� �˷� �ݴϴ�.
	====================================================================*/
	backGround = IMG_M->findImage("hardStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		���������� ���� ��ġ�մϴ�. LT, RT, RB, LB ��!!
	====================================================================*/
	backWallInit(vector3(0, WINSIZEY, 0), vector3(1705, WINSIZEY, 0), vector3(1705, 0, 895), vector3(0, 0, 895));

	leftWallInit(vector3(0, WINSIZEY, 0), vector3(0, WINSIZEY, 0), vector3(0, 0, 1428), vector3(0, 0, 1428));

	rightWallInit(vector3(1705, WINSIZEY, 0), vector3(2235, WINSIZEY, 0), vector3(2235, 0, 1428), vector3(1705, 0, 895));

	floorInit(vector3(0, 0, 895), vector3(2328, 0, 895), vector3(2328, 0, 1428), vector3(0, 0, 1428));

	poolInit(vector3(0, 0, 1150), vector3(1480, 0, 1150), vector3(1760, 0, 1428), vector3(0, 0, 1428));
	/*====================================================================
		������Ʈ�� ���ʹ̸� ��ġ�մϴ�.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::LADDER, vector3(1555, 0, 930));
	_objectM->pushObject(OBJECT_TYPE::HARDPLATFORM, vector3(850, 0, 600));
	/*====================================================================
		�������� ���� �� ���� �� �̺�Ʈ�� �߰��մϴ�.
	====================================================================*/

	return S_OK;
}

void HardStage::release()
{
	Stage::release();
}

void HardStage::update()
{
	Stage::update();
}

void HardStage::render()
{
	Stage::render();
}
