#include "stdafx.h"
#include "enemyWeaponHit.h"
#include "Enemy.h"

void enemyWeaponHit::EnterState()
{
	SOUND_M->play("enemy_down", SFXVOLUME);
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);
}

void enemyWeaponHit::UpdateState()
{
	//HIT의 상태가 끝났다.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyWeaponHit::ExitState()
{
}
