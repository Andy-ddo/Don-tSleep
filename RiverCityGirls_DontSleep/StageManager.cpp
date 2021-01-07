#include "stdafx.h"
#include "StageManager.h"

#include "Player.h"
#include "Boss.h"

#include "EasyStage.h"
#include "NormalStage.h"
#include "HardStage.h"
#include "BossStage.h"


/*====================================================================
	�ʱ�ȭ���� �÷��̾ ����� �ָ�, ù ���������� �����մϴ�.
	�⺻ ���� EASY�̸�, �����ϰ� ���� ���������� �����ϸ� �ش� ���������� ���õ˴ϴ�.
====================================================================*/
HRESULT StageManager::init()
{
	//�÷��̾� ��ü ����
	_player = new Player;
	_player->init();
	_player->setLinkStageM(this);
	EVENT_M->setLinkPlayer(_player);

	//_boss = new Boss;
	
	
	
	


	//ù �������� ����
	setStage(STAGETYPE::EASY);

	return S_OK;
}

/*====================================================================
	Player�� Stage�� �޸𸮸� ������ �ݴϴ�.
====================================================================*/
void StageManager::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_stage->release();
	SAFE_DELETE(_stage);

	/*_boss->release();
	SAFE_DELETE(_boss);*/
}	

/*====================================================================
	Player�� Stage�� ���� �� ������Ʈ �ϸ�,
	�̺�Ʈ�� ���� ������ ���� ������ ī�޶� �÷��̾ ���� ���ϴ�.
====================================================================*/
void StageManager::update()
{
	_stage->update();
	_player->update();
	//_boss->update();
	

	if (!EVENT_M->isEvent()) CAMERA_M->SetPos(_player->getObj().pos.x, _player->getObj().pos.z, 0, 0, 4.0f);
	// ����׿����������(21.01.07 ���η���)
	if (KEY_M->isOnceKeyDown(VK_F1)) setStage(STAGETYPE::EASY);
	if (KEY_M->isOnceKeyDown(VK_F2)) setStage(STAGETYPE::NORMAL);
	if (KEY_M->isOnceKeyDown(VK_F4)) setStage(STAGETYPE::HARD);
	if (KEY_M->isOnceKeyDown(VK_F5)) setStage(STAGETYPE::BOSS);
}

/*====================================================================
	Player�� Stage�� ���� �մϴ�.
====================================================================*/
void StageManager::render()
{
	_stage->render();
	_player->render();
}

/*====================================================================
	setStage �Լ��� enum class STAGETYPE�� ���ڰ����� �޾�,
	���� ���������� �ش� ���������� ���� �� �ݴϴ�.
====================================================================*/
void StageManager::setStage(STAGETYPE current)
{
	if (_stage != NULL)
	{
		if (_currentStage == current) return;	//���� ���������� ���� ��� ���������� �ٲ��� �ʴ´�.

		_stage->release();		//���������� ������� ������, �ٲٱ� ����
		SAFE_DELETE(_stage);	//�޸𸮸� ���� �ְ� ����Ʈ �� �ش�.
	}

	_preStage = _currentStage;
	_currentStage = current;	//���� ���������� �ٲ� �ش�.

	//���ο� �������� ��ü�� �����ϰ�, �ʱ�ȭ�Ѵ�.
	switch (_currentStage)
	{
	case STAGETYPE::EASY:
		_stage = new EasyStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::NORMAL:
		_stage = new NormalStage;
		_stage->setLinkStageM(this);
		_stage->init();

		break;

	case STAGETYPE::HARD:
		_stage = new HardStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::BOSS:
		_stage = new BossStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;
	}

	//�÷��̾ �������� �ʱ�ȭ�� �Ѵ�.
	_player->stageInit();

}


