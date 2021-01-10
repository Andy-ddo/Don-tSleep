#pragma once

class StageManager;
class Player;
class Enemy;

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
	// �� �浹
	void playerWallCollsion();
	void enemyWallColiision(GameObject* character);

	// �浹 �Լ�
	void playerObjectCollision();
	void enemyObjectCollision(GameObject* character);

	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkPlayer(Player* player) { _player = player; }
};

