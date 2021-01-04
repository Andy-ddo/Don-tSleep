#pragma once
#include "Linear.h"

/*====================================================================
	Z-Order�� �浹 ó���� ���� Player, Enemy, Object ��
	���� ������Ʈ�� ��ü������ ���̴� GameObject Ŭ�����Դϴ�.
====================================================================*/
class GameObject
{
public:
	OBJECT_GROUP group;		//�׷�

	image* img;				//�̹���
	POINT imgIndex;			//������ �ε���
	animation* ani;			//�ִϸ��̼�

	vector3 pos;			//��ġ
	vector3 prePos;			//���� ��ġ
	vector3 size;			//ũ�� (x,z)
	RECT rc;				//��Ʈ

	Linear topPlane[4];		//�� ���
	Linear bottomPlane[4];	//�Ʒ� ���
	Linear sideHeight[4];	// �׸��� ���� ���е�, �浹 ó������ �� ��

	int alpha;				//�������� (0~255)

	float angle;			//����
	float angle2;			//����

	bool isActive;			//Ȱ��ȭ ����
	bool isShadow;			//�׸��ڰ� �ִ���

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init(OBJECT_GROUP _group, image* _img, vector3 _pos);				//�ʱ�ȭ
	virtual void init(OBJECT_GROUP _group, image* _img, vector3 _pos, float a);		//������Ʈ ���� �ʱ�ȭ
	virtual void release();
	virtual void update();
	virtual void render();

	void RectRenew();		//��Ʈ ����

	void PolyLineRender(HDC hdc);	//������ �� ����
};
