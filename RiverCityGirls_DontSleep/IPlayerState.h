#pragma once
#include "gameNode.h"
#include "Player.h"

class Player;

class IPlayerState: public gameNode
{
protected:
	Player* _thisPl;

public:
	IPlayerState() {}
	~IPlayerState() {}

	//�÷��̾� ��Ŀ
	void LinkPlAddress(Player* pl) { _thisPl = pl; }

	//���¸����� ����
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
};

