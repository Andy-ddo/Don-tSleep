#include "stdafx.h"
#include "playGround.h"

#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "ShopScene.h"
#include "EndingScene.h"

// ============================ ����� �� ============================
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
// ==================================================================

/*====================================================================

	�÷��̱׶��� �ʱ�ȭ�Դϴ�. �̰����� �̹����� ���� �����մϴ�.
	setScene �� changeScene�� ���� ���� ���� �����մϴ�.
	title�� �⺻�̸�, �׽�Ʈ�ϰ� ���� ���� �ִٸ� init���� �ش� ������ change ���ּ���.

====================================================================*/
HRESULT playGround::init()
{
	gameNode::init(true);
	AddFontResourceA("source/font/CookieRun Bold.otf");
	addImage();							//�̹��� ����
	addScene();							//�� ����
	SCENE_M->changeScene("game");		//��Ȱ�� ������� ���� game ������ ����.
	//SCENE_M->changeScene("title");		//ù ���۾� (title)
	return S_OK;
}

void playGround::release()
{
	gameNode::release();
}

/*====================================================================

	�÷��̱׶��� ������Ʈ�Դϴ�. �⺻������ �׻� ���� ���� ������Ʈ ������,
	���� ��� �߿��� ������ ������Ʈ�� ����� �ϹǷ� �̺�Ʈ �Ŵ�����
	������ ��� ���̶�� �ϸ� ���� ���� ������Ʈ�� ���� �ʰ� return�մϴ�.

====================================================================*/
void playGround::update()
{
	gameNode::update();					//���� ��忡�� �Ŵ������� ������Ʈ�Ѵ�.

	if (EVENT_M->getIsMovie()) return;		//���� ��� �߿��� ������Ʈ ���� �ʴ´�.

	CAMERA_M->update();					//ī�޶� ������Ʈ �Ѵ�.
	UI_M->update();						//UI ������Ʈ
	SCENE_M->update();					//�� ������Ʈ

	if (KEY_M->isOnceKeyDown(VK_LBUTTON))
	{
		cout << "���콺 X��ǥ: " << _ptMouse.x << endl;
		cout << "���콺 Y��ǥ: " << _ptMouse.y << endl;
	}
	
}

/*====================================================================

	�÷��� �׶��忡�� ������ �ϸ�, �⺻������ BackDC�� �Ͼ� ����� ���,
	���� ��� �߿� ���߹��۸��� ���� ���ƾ� �ϱ� ������ return�մϴ�.

	�̺�Ʈ �Ŵ����� ���� ��� ���� �ƴ� ���,
	���� mapDC�� �����ϰ�, ī�޶� map�� UI�� backDC�� �����մϴ�.
	TAB�� ����� ��� fps �� ������ ������ ����Ǹ�,
	���������� HDC�� backDC�� ���� ���۸��մϴ�.

====================================================================*/
void playGround::render()
{
	PatBlt(getBackDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);	//�Ͼ� ���
	
	//================ ���� ���� =================
	if (EVENT_M->getIsMovie()) return;	//���� ��� �߿��� �������� �ʴ´�.
	SCENE_M->render();								//�� ����

	CAMERA_M->render(getBackDC(),_mapBuffer);		//ī�޶� ����
	EVENT_M->render(getBackDC());
	//================= ����� �� =================
	//FPS Ȯ��
	if (KEY_M->isToggleKey(VK_TAB)) TIME_M->render(getBackDC());

	//================= ���� ���۸� =================
	_backBuffer->render(getHDC());
}

/*====================================================================

	���� �����մϴ�. Ÿ��Ʋ, ����, ����, ���� �װ����� �ֽ��ϴ�.
	�������� ���ν��� ��ü�� ���� ������ �̵��� �Ұ����մϴ�.

====================================================================*/
void playGround::addScene()
{
	SCENE_M->addScene("title", new TitleScene);			//Ÿ��Ʋ �� �߰�
	SCENE_M->addScene("select", new SelectScene);		//���� �� �߰�
	SCENE_M->addScene("loading", new LoadingScene);		//�ε� �� �߰�
	SCENE_M->addScene("game", new GameScene);			//���� �� �߰�
	SCENE_M->addScene("shop", new ShopScene);			//���� �� �߰�
	SCENE_M->addScene("ending", new EndingScene);		//���� �� �߰�
}

