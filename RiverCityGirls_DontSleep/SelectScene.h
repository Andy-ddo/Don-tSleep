#pragma once
#include "Scene.h"
#include "Select.h"
#include <functional>

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
	Select* _charSelect;		//ĳ���� ����

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

	void load();		//�ε� ��ư �ݹ� �Լ�


	void setState(SELECTTYPE type);
};

