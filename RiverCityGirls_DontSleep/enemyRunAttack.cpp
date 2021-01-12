#include "stdafx.h"
#include "enemyRunAttack.h"
#include "Enemy.h"

void enemyRunAttack::EnterState()
{
	_thisEn->SetImage();
	LookAtPlayer();
	RECT temp;
	if (IntersectRect(&temp, &_thisEn->getInfo().rcAttack, &_thisEn->getPlayerAddress()->getRefObj().rc))
	{
		EFFECT_M->play("ef_attack", (_thisEn->getInfo().rcAttack.left + _thisEn->getInfo().rcAttack.right) / 2,
			(_thisEn->getInfo().rcAttack.top + _thisEn->getInfo().rcAttack.bottom) / 2);
	}
}

void enemyRunAttack::UpdateState()
{

	Attack();


}

void enemyRunAttack::ExitState()
{
	_thisEn->getInfo().isAttack = false;

}
