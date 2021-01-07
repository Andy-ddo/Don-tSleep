#pragma once
#include "singletonBase.h"
#include <queue>
#include "Event.h"

class Player;

/*====================================================================
	�̺�Ʈ�� ť�� ��� �����ϴ� �̺�Ʈ �Ŵ����Դϴ�.
====================================================================*/
class EventManager : public singletonBase <EventManager>
{
private:
	queue<Event*> _qEvent;		//�̺�Ʈ�� ��� �̺�Ʈ ť

	bool _isMovie;				//���� ��� ������
	Player* _player;			//�÷��̾� ��ũ

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	

	/*====================================================================
									FUNCTION
	====================================================================*/
	//�̺�Ʈ �߰�
	void addEvent(Event* eve);		

	/*====================================================================
									SETTER
	====================================================================*/
	//�÷��̾�� ����
	void setLinkPlayer(Player* player) { _player = player; }

	/*====================================================================
									GETTER
	====================================================================*/
	//�̺�Ʈ ���� ����
	bool isEvent();

	//���� ��� ������
	bool isMovie();

};

