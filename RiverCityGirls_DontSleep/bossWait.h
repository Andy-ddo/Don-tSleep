#pragma once
#include"IBossState.h"

class StageManager;
class Player;
class Boss;

class bossWait :public IBossState
{

private: 
	int _count;			// ���͹��� �ֱ� ���� ��Ʈ
	Boss* _boss;
public:

	Boss* getBossAddress() { return _boss; }

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
