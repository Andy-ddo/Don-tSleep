#include "stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init()
{
	return S_OK;
}

void UIManager::release()
{
}

/*====================================================================
					Ȱ��ȭ�� UI�� ������Ʈ �մϴ�.
====================================================================*/
void UIManager::update()
{
	if (KEY_M->isOnceKeyDown(VK_F3))
	{
		_isActive = !_isActive;
	}

	if (_mUI.empty()) return;
	if (!_isActive) return;

	for (auto _miUI = _mUI.begin(); _miUI != _mUI.end(); ++_miUI)
	{
		if (!_miUI->second->isActive) continue;
		_miUI->second->update();
	}
}

/*====================================================================
					Ȱ��ȭ�� UI�� ���� �մϴ�.
====================================================================*/
void UIManager::render(HDC hdc)
{
	if (_mUI.empty()) return;
	if (!_isActive) return;

	for (auto _miUI = _mUI.begin(); _miUI != _mUI.end(); ++_miUI)
	{
		if (!_miUI->second->isActive) continue;
		_miUI->second->render(hdc);
	}
}

/*====================================================================
					���� �̹����� UI�� �߰��մϴ�.
====================================================================*/
void UIManager::addImage(string name, image* img, vector3 pos)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new UI;
	ui->type = UITYPE::UI;
	ui->img = img;
	ui->pos = pos;
	ui->isActive = false;

	_mUI.insert(make_pair(name, ui));
}

/*====================================================================
						UI�� �����մϴ�.
====================================================================*/
void UIManager::popUI(string name)
{
	if (_mUI.empty()) return;

	for (auto _miUI = _mUI.begin(); _miUI != _mUI.end();)
	{
		if (name == _miUI->first)
		{
			SAFE_DELETE(_miUI->second);
			_miUI = _mUI.erase(_miUI);
		}
		else ++_miUI;
	}
}

/*====================================================================
		UI�� ã�� �����մϴ�. UI ���� �Լ��� ����� �� �ְ� �˴ϴ�.
====================================================================*/
UI * UIManager::findUI(string name)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return _miUI->second;
	return nullptr;
}