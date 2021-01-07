#pragma once
#include "singletonBase.h"

// ���� �����͸� ������ �־���ϳ�?
struct tagSaveLoadData
{
	const char* subject;
	const char* title;
	const char* body;
};

struct tagStageData
{
	Player* _playerData;
	// ���Ŀ� ������ �߰�(�κ��丮?)


};


class DataManager : public singletonBase<DataManager>
{
private:
	typedef vector<tagSaveLoadData>					arrSaveLoadData;
	typedef vector<tagSaveLoadData>::iterator		arrSaveLoadIter;

	typedef vector<arrSaveLoadData>					vSaveLoadDataList;
	typedef vector<arrSaveLoadData>::iterator		vSaveLoadDataIter;
private:
	vSaveLoadDataList _vDatas;

	tagStageData _stageData;

public:
	DataManager();
	~DataManager();

	HRESULT init();

	// ������ �߰�?
	void updateStageData(Player* player);

};

