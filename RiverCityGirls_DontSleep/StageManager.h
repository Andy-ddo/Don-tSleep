#pragma once

class Player;
class Stage;

/*====================================================================
	StageManager��, �÷��̾�� ���������� ����� ������,
	������������ Easy, Normal, Hard, Boss�� �ֽ��ϴ�.
	���������� '���� �������� ����'�� �����ϸ�, ���� �������� �����մϴ�.
====================================================================*/

class StageManager
{
	Player* _player;
	Stage* _stage;
	STAGETYPE _currentStage;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();	
	virtual void render();

	/*====================================================================
									SETTER
	====================================================================*/
	virtual void setStage(STAGETYPE current);


	/*====================================================================
									GETTER
	====================================================================*/
	Stage* getStage() { return _stage; }
	Player* getPlayer() { return _player; }

};

