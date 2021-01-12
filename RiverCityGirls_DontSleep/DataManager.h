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
	int playerHp;
	vector3 playerPos;
	bool eventEnd;



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


public:
	DataManager();
	~DataManager();

	HRESULT init();

	//������ �߰� �Լ�
	void addData(const char* subject, const char* title, const char* body);
	//ini���� ������ִ� �Լ�
	void iniSave(const char* fileName);

	//���ڿ� ������ �ҷ����� �Լ�
	string loadDataString(const char* fileName, const char* subject, const char* title);

	//���� ������ �ҷ����� �Լ�
	int loadDataInterger(const char* fileName, const char* subject, const char* title);

	

};

