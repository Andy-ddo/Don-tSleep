#include "stdafx.h"
#include "bossMeteor.h"
#include "Boss.h"

void bossMeteor::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_meteor");
}

void bossMeteor::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("Bs_meteor");
	}
}

void bossMeteor::ExitState()
{
}
