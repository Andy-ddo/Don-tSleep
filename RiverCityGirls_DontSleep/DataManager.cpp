#include "stdafx.h"
#include "DataManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

HRESULT DataManager::init()
{
	return S_OK;
}

void DataManager::addData(const char * subject, const char * title, const char * body)
{
	// ������ �߰�
}

void DataManager::iniSave(const char * fileName)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vDatas.size(); ++i)
	{
		arrSaveLoadData data = _vDatas[i];
		WritePrivateProfileString(data[0].subject, data[0].title, data[0].body, str);
		data.clear();
	}

	_vDatas.clear();
}

void DataManager::saveStageData(Player* player, StageManager* stage)
{
	//�÷��̾� ������
	_data.playerPos = player->getObj().pos;
	_data.hp = player->getInfo().hp;
	_data.maxHP = player->getInfo().maxHP;
	_data.force = player->getInfo().force;
	_data.coin = player->getInfo().coin;
	_data.LV = player->getInfo().LV;
	_data.exp = player->getInfo().exp;

	//�������� ������
	switch (stage->getCurStage())
	{
	case STAGETYPE::EASY:
		_data.curStage = 0;
		break;
	case STAGETYPE::NORMAL:
		_data.curStage = 1;
		break;
	case STAGETYPE::HARD:
		_data.curStage = 2;
		break;
	case STAGETYPE::BOSS:
		_data.curStage = 3;
		break;
	default:
		break;
	}


}

void DataManager::loadStageData(Player * player, StageManager * stage)
{
	////�������� ������
	//switch (_data.curStage)
	//{
	//case 0:
	//	stage->setStage(STAGETYPE::EASY);
	//	break;
	//case 1:
	//	stage->setStage(STAGETYPE::NORMAL);
	//	break;
	//case 2:
	//	stage->setStage(STAGETYPE::HARD);
	//	break;
	//case 3:
	//	stage->setStage(STAGETYPE::BOSS);
	//	break;
	//default:
	//	break;
	//}
	//stage->getStage()->setLockEventEnd(_data.lockEventEnd);

	//�÷��̾� ������
	player->getPObj()->pos = _data.playerPos;
	player->getInfo().hp = _data.hp;
	player->getInfo().maxHP = _data.maxHP;
	player->getInfo().force = _data.force;
	player->getInfo().coin = _data.coin;
	player->getInfo().LV = _data.LV;
	player->getInfo().exp = _data.exp;

}

void DataManager::loadStageData()
{
	////�������� ������
	//switch (_data.curStage)
	//{
	//case 0:
	//	_stageM->setStage(STAGETYPE::EASY);
	//	break;
	//case 1:
	//	_stageM->setStage(STAGETYPE::NORMAL);
	//	break;
	//case 2:
	//	_stageM->setStage(STAGETYPE::HARD);
	//	break;
	//case 3:
	//	_stageM->setStage(STAGETYPE::BOSS);
	//	break;
	//default:
	//	break;
	//}
	//_stageM->getStage()->setLockEventEnd(_data.lockEventEnd);

	//�÷��̾� ������
	_player->getPObj()->pos = _data.playerPos;
	_player->getInfo().hp = _data.hp;
	_player->getInfo().maxHP = _data.maxHP;
	_player->getInfo().force = _data.force;
	_player->getInfo().coin = _data.coin;
	_player->getInfo().LV = _data.LV;
	_player->getInfo().exp = _data.exp;

}

string DataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = {};
	GetPrivateProfileString(subject, title, "", data, 64, str);

	string strData = data;


	return strData;
}

int DataManager::loadDataInterger(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);


	return GetPrivateProfileInt(subject, title, 0, str);
}

void DataManager::checkData()
{
	cout << "�÷��̾� ��ġX: " << _data.playerPos.x << endl;
	cout << "�÷��̾� ��ġY: " << _data.playerPos.y << endl;
	cout << "�÷��̾� ��ġZ: " << _data.playerPos.z << endl;
	cout << "�÷��̾� hp: " << _data.hp << endl;
	cout << "�÷��̾� maxHP: " << _data.maxHP << endl;
	cout << "�÷��̾� coin: " << _data.coin << endl;
	cout << "�÷��̾� force: " << _data.force << endl;
	cout << "�÷��̾� LV: " << _data.LV << endl;
	cout << "�÷��̾� exp: " << _data.exp << endl;

	cout << "�÷��̾� ���� ��������: " << _data.curStage << endl;
	cout << "�÷��̾� ������ �̺�Ʈ: " << _data.lockEventEnd << endl;
}

void DataManager::setPlayerHP(int num)
{
	_data.hp = num;
}

void DataManager::plusPlayerHP(int num)
{
	_data.hp += num;
	if (_data.hp > _data.maxHP) _data.hp = _data.maxHP;
}

bool DataManager::minusPlayerCoin(float numf)
{
	if (_data.coin < numf) return false;
	_data.coin -= numf;
	return true;
}

void DataManager::setLinkPlayer(Player* player)
{
	_player = player;
}

void DataManager::setLinkStageM(StageManager* stageM)
{
	_stageM = stageM;
}