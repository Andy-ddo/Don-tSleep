#include "stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init()
{
	/*====================================================================
		���� ������ ���̺� ������ �ε��� �� �ְ� �մϴ�.
		���̺� ����, ĳ���� ����, �ɼ�, �޴��� â �� ���� ���� ���� ��� ������ �մϴ�.
	====================================================================*/

	/*====================================================================
		���� ����� �����ϰ�, Ÿ��Ʋ�� UI�� ����ϸ�, ����� ������ŵ�ϴ�.
	====================================================================*/
	_background = IMG_M->findImage("select_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);
	_background2 = IMG_M->findImage("select_background2");

	/*====================================================================
		�� ĳ���� �̹����� ���� �������� �̵���ŵ�ϴ�.
	====================================================================*/
	_illust = IMG_M->findImage("select_illust");
	_illustPos = vector3(350.0f, WINSIZEY / 2 + 360.0f, 0.0f);
	_illustInter = new Interpolation;
	_illustInter->moveTo(&_illustPos, 450, WINSIZEY / 2 + 360, 0.5f);
	_ratioOffset = 0.001f;

	/*====================================================================
		UI�� ���� �̹����� �߰��ϰ�, ������ �� �ֵ��� �մϴ�.
	====================================================================*/
	//�ε� ���� ���� ��ư
	_loadSelect = new Select;
	_loadSelect->addButton(Button(IMG_M->findImage("save_load_close"), IMG_M->findImage("save_load_open"), vector3(900, (WINSIZEY - 150) / 4 * 1, 0), std::bind(&SelectScene::load, this), 0));
	_loadSelect->addButton(Button(IMG_M->findImage("save_load_close"), IMG_M->findImage("save_load_open"), vector3(900, (WINSIZEY - 150) / 4 * 2, 0), std::bind(&SelectScene::load, this), 1));
	_loadSelect->addButton(Button(IMG_M->findImage("save_load_close"), IMG_M->findImage("save_load_open"), vector3(900, (WINSIZEY - 150) / 4 * 3, 0), std::bind(&SelectScene::load, this), 2));
	_loadSelect->addButton(Button(IMG_M->findImage("save_load_close"), IMG_M->findImage("save_load_open"), vector3(900, (WINSIZEY - 150) / 4 * 4, 0), std::bind(&SelectScene::load, this), 3));

	//ĳ���� ���� ��ư�� �̹���
	_charSelect = new Select;
	_charSelect->addButton(Button(IMG_M->findImage("select_kyoko2"), IMG_M->findImage("select_kyoko"), vector3(WINSIZEX/2 + 100, WINSIZEY / 2, 0), std::bind(&SelectScene::load, this), 0));
	_charSelect->addButton(Button(IMG_M->findImage("select_misako2"), IMG_M->findImage("select_misako"), vector3(WINSIZEX/2 + 450, WINSIZEY / 2, 0), std::bind(&SelectScene::load, this), 1));

	//�ɼ� UI�� ��ư


	//�޴��� UI�� ��ư


	/*====================================================================
		ù ���¸� �ε�� �����մϴ�. LOAD - OPTION - MANUAL �Ŀ� �ε������� �̾����ϴ�.
	====================================================================*/
	setState(SELECTTYPE::LOAD);

	return S_OK;
}

void SelectScene::release()
{
}

void SelectScene::update()
{
	/*====================================================================
		ĳ���� �Ϸ���Ʈ�� �̵��� Ȯ�� ��� ȿ���� �����ϰ�
		����� x+1, y+1 �밢�� �������� ���� ��ŵ�ϴ�.
	====================================================================*/
	loop.x++; loop.y++;

	_illustInter->update();
	_ratioOffset = (TIME_M->getWorldTime() - _ratioTime) * 0.04f;
	if (TIME_M->getWorldTime() - _ratioTime > 0.35f) _ratioTime = TIME_M->getWorldTime();

	/*====================================================================
		ī�޶�� �߾ӿ� ������Ű��, ���͸� ġ�� ���� ������ �ѱ�ϴ�.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	/*====================================================================

	====================================================================*/
	switch (_state)
	{
		/*====================================================================
			��ư�� �����ϰ�, ������ �� �Ŀ��� ĳ���� �������� �Ѿ�ϴ�.
		====================================================================*/
		case SELECTTYPE::LOAD:
		if (_loadSelect->update()) setState(SELECTTYPE::CHARACTER);
		break;

		/*====================================================================
			ĳ���͸� �����ϰ�, �ɼ�â���� �Ѿ�ϴ�.
		====================================================================*/
		case SELECTTYPE::CHARACTER:
		if(_charSelect->update()) setState(SELECTTYPE::OPTION);
		break;
		/*====================================================================
			���� ���� �� �ɼ� â�� ����, �������� �Ѿ�ϴ�.
		====================================================================*/
		case SELECTTYPE::OPTION:
		if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)))
		{
			setState(SELECTTYPE::MANUAL);
		}
		break;

		/*====================================================================
			�޴��� UI�� ����, ���� �ε������� �����մϴ�.
		====================================================================*/
		case SELECTTYPE::MANUAL:
		if (!EVENT_M->getIsEvent())
		{
			if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)))
			{
				SCENE_M->changeScene("loading");			//�ε� ������ ����
			}
		}
		break;
		default:
		break;
	}
}

void SelectScene::render()
{
	/*====================================================================
		����� loop ���� ���� ���� �����ϰ�, ĳ���� �̹����� ��� �ݴϴ�.
	====================================================================*/
	_background->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
	_background2->render(getMapDC());
	IMG_M->findImage("start_frame")->render(getMapDC(), 800, 450, 1280 / 1600.0f, 720 / 900.0f);
	_illust->render(getMapDC(), _illustPos.x - _illustPos.x*_ratioOffset, _illustPos.y - _illustPos.y *_ratioOffset, 0.7f + _ratioOffset, 0.7f + _ratioOffset);

	switch (_state)
	{
		case SELECTTYPE::LOAD:
		_loadSelect->render(getMapDC());
		break;
		case SELECTTYPE::CHARACTER:
			IMG_M->findImage("select_kyoko_background")->render(getMapDC(), WINSIZEX / 2 + 100, WINSIZEY / 2);
			IMG_M->findImage("select_misako_background")->render(getMapDC(), WINSIZEX / 2 + 450, WINSIZEY / 2);
			_charSelect->render(getMapDC());
		break;
		case SELECTTYPE::OPTION:

		break;
		case SELECTTYPE::MANUAL:

		break;
		default:
		break;
	}

}

/*====================================================================
	��ư ���ÿ� ���� ���̺� ������ �ε��մϴ�.
====================================================================*/
void SelectScene::load()
{
	
}

/*====================================================================
	���� ���� ���¸� �����մϴ�.
====================================================================*/
void SelectScene::setState(SELECTTYPE type)
{
	_state = type;

	switch (_state)
	{
		case SELECTTYPE::LOAD:


		break;
		case SELECTTYPE::CHARACTER:
			

		break;
		case SELECTTYPE::OPTION:


		break;
		case SELECTTYPE::MANUAL:

		break;
		default:
		break;
	}
	/*====================================================================
		ȭ�� ���°� �ٲ� ������ ī�޶� �����Ӱ� ��� �̺�Ʈ�� �����մϴ�.
	====================================================================*/
	EVENT_M->addEvent(new waitForSec(0.3f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.1f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.05, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
}
