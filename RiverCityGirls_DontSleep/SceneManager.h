#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class SceneManager : public singletonBase<SceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//씬추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	//릴리즈, 이닛하며 씬을 변경하는 함수
	HRESULT changeScene(string sceneName);

	//이닛하지 않고 씬만 변경하는 함수
	HRESULT setScene(string sceneName);

	SceneManager() {};
	~SceneManager() {};
};

