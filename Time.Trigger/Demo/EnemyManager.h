#pragma once
class Enemy;
class EnemyManager : public IGameObject
{
	public:
	EnemyManager();
	~EnemyManager();
	bool Init();
	void Update();
	void Render(RenderContext& rc);

private:
	std::vector<Enemy*> enemies;  // “G‚ğ•¡”ŠÇ—‚·‚é
};

