#pragma once

class StageManager;
class Player;

class CollisionManager
{
private:
	StageManager* _stageM;
	Player* _player;
	int testNum = 0;
public:
	CollisionManager() {};
	~CollisionManager() {};

	HRESULT init();
	void release();



	// ���� �¿� �浹 ����
	void LRUDCollision(GameObject* character, GameObject* obj);
	// ���� ����
	void objectCollision();
	void wallCollsion();

	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkPlayer(Player* player) { _player = player; }
};

