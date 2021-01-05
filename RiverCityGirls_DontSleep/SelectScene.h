#pragma once
#include "Scene.h"
#include "Select.h"

enum class SELECTTYPE
{
	LOAD,
	OPTION,
	MANUAL,
	CHARACTER,
};


class SelectScene : public Scene
{
private:
	SELECTTYPE _state;			//���� ���� ���� ����

	Select* _loadSelect;		//�ε��� ���� ����

	vector3 loop;				//��� ����

	image* _background2;		//���2

	image* _illust;				//���� ĳ���� �Ϸ���Ʈ
	vector3 _illustPos;
	Interpolation* _illustInter;
	float _ratioOffset;
	float _ratioTime;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	static void load0();		//�ε� ��ư �ݹ� �Լ�
	static void load1();
	static void load2();
	static void load3();

	void setState(SELECTTYPE type);
};

