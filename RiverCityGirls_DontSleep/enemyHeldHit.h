#pragma once
#include "IEnemyState.h"
class enemyHeldHit : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

