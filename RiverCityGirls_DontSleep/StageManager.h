#pragma once


class Player;
class Boss;
class Stage;

/*====================================================================
	StageManager��, �÷��̾�� ���������� ����� ������,
	������������ Easy, Normal, Hard, Boss�� �ֽ��ϴ�.
	���������� '���� �������� ����'�� �����ϸ�, ���� �������� �����մϴ�.
====================================================================*/

class StageManager
{
	Player* _player;
	Boss* _boss;
	Stage* _stage;
	STAGETYPE _currentStage;
	STAGETYPE _preStage;
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
	Boss* getBoss() { return _boss; }
	STAGETYPE getCurStage() { return _currentStage; }
	STAGETYPE getPreStage() { return _preStage; }

};

