#pragma once
#include"IBossState.h"

class bossWait :public IBossState
{

private: 
	int _count;			// ���͹��� �ֱ� ���� ��Ʈ
	bool _isWait;		// �ൿ�� �����ϱ� ���� ��
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
