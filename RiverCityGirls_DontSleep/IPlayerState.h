#pragma once
#include "gameNode.h"

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

	//������Ʈ����
	bool pauseUpdate();

	//�ȱ⵿��
	void walkPattern();
	//�⺻���� (�ȱ�/���/����)
	void basePattern();

	//�����̵�
	void lineMove(float speed);
	//�¿��̵�
	void crossMove(float speed);
};

