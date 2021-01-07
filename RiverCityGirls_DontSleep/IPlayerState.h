#pragma once
#include "gameNode.h"
#include "Player.h"

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

	//�ȱ⵿��
	void walkPattern();
	//�⺻���� (�ȱ�/���/����)
	void basePattern();

	//���ݻ��¸� ���������� ��ȯ
	void checkAttack();

	//�����̵�
	void lineMove(float speed);
	//�¿��̵�
	void crossMove(float speed);

	//������Ʈ �Ͻ�����
	bool pauseUpdate();
	//������ ��� �������� Ȯ��, ������ �������̸� �Ű����� true
	bool isEndFrame(bool reverse);
};

