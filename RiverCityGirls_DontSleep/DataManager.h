#pragma once
#include "singletonBase.h"

class Player;
class StageManager;

// ���� �����͸� ������ �־���ϳ�?
struct tagSaveLoadData
{
	const char* subject;
	const char* title;
	const char* body;
};




class DataManager : public singletonBase<DataManager>
{
	struct tagStageData
	{
		// player
		vector3 playerPos;
		int hp;
		int maxHP;
		int force;
		float coin;
		int LV;
		float exp;

		// stage
		int curStage;
		bool lockEventEnd;
	};


private:
	typedef vector<tagSaveLoadData>					arrSaveLoadData;
	typedef vector<tagSaveLoadData>::iterator		arrSaveLoadIter;

	typedef vector<arrSaveLoadData>					vSaveLoadDataList;
	typedef vector<arrSaveLoadData>::iterator		vSaveLoadDataIter;
private:
	vSaveLoadDataList _vDatas;
	tagStageData _data;

	Player* _player;
	StageManager* _stageM;
public:
	DataManager();
	~DataManager();

	HRESULT init();

	//������ �߰� �Լ�
	void addData(const char* subject, const char* title, const char* body);
	//ini���� ������ִ� �Լ�
	void iniSave(const char* fileName);

	void saveStageData(Player* player, StageManager* stage);
	void loadStageData(Player* player, StageManager* stage);
	void loadStageData();
	//���ڿ� ������ �ҷ����� �Լ�
	string loadDataString(const char* fileName, const char* subject, const char* title);

	//���� ������ �ҷ����� �Լ�
	int loadDataInterger(const char* fileName, const char* subject, const char* title);

	void checkData();
	void setPlayerHP(int num);
	void plusPlayerHP(int num);
	bool minusPlayerCoin(float numf);
	void setLinkPlayer(Player* player);
	void setLinkStageM(StageManager* stageM);
};

