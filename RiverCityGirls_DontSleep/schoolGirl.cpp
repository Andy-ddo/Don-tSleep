#include "stdafx.h"
#include "schoolGirl.h"
#include "Player.h"

#include "enemyIDLE.h"


HRESULT schoolGirl::init()
{
	Enemy::init();
	//�̹��� ��ϵ� ���س���                            �� schoolGirlIdle ��� ������� ������..�Ф� 
	_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlIdle"),_obj.pos);

	SetState(EN_STATE::EN_IDLE);
	_dest = DIRECTION::RIGHT;

	return S_OK;
}

void schoolGirl::release()
{

}

void schoolGirl::update()
{
	Enemy::update();
	//_EState->UpdateState();
	//SetState(EN_STATE::EN_IDLE);
	//���ݹ޾Ҵ��� ���θ� �˼�����!
	if (_player->getInfo().isAttack)cout << "���ݹ���" << endl;
	//�뽬�����ݾ��� / �������� / Ŀ�ǵ������ �Ұ��ϳ� �־����! �ѹ� �¾����� ���̻� �ȸ°�!
}

void schoolGirl::render()
{

}
