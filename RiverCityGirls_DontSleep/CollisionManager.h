#pragma once

class StageManager;
class Player;
class Enemy;

class CollisionManager
{
private:
	StageManager* _stageM;
	Player* _player;
	Enemy* _enemy;
	bool checkLeft;
	bool checkRight;
	bool checkUp;
	bool checkDown;
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
	void enemyObjectCollision(Enemy* enemy);

	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkPlayer(Player* player) { _player = player; }

	void destructObject();
	void bossDestructObject(Enemy* enemy);
};

