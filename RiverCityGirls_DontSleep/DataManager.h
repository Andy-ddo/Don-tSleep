#pragma once
#include "singletonBase.h"



// ���� �����͸� ������ �־���ϳ�?
struct tagSaveLoadData
{
	const char* subject;
	const char* title;
	const char* body;
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



	

};

