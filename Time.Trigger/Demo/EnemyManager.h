#pragma once

class Enemy;
class Player;

class EnemyManager : public IGameObject
{
	public:
	EnemyManager();
	~EnemyManager();
	bool Init();
	void Update();
	void Render(RenderContext& rc);

	void SetPlayer(Player* player) { m_player = player; }

	void CheckCollision();

private:
	std::vector<Enemy*> enemies;  // 敵を複数管理する

	Player* m_player = nullptr; // プレイヤーの参照


};

