#pragma once
#include "gameNode.h"
#include "Boss.h"

class Boss;

class IBossState : public gameNode
{
protected:
	Boss* _thisBs;

public:
	IBossState() {}
	~IBossState() {}

	//�÷��̾� ��Ŀ
	void LinkPlAddress(Boss* bs) { _thisBs = bs; }

	//���¸����� ����
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

	void move(float speed);
	
};
