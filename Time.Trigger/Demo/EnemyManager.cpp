#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager() {}
EnemyManager::~EnemyManager()
{
    for (auto e : enemies) {
        DeleteGO(e);
    }
    enemies.clear();
}

bool EnemyManager::Init()
{
    // —á: 3‘Ì‚Ì“G‚ğo‚·
    {
        Enemy* e = NewGO<Enemy>(0, "enemy1");
        e->SetInitPos({ 0.0f, -100.0f, -1000.0f });
        e->Init();
        enemies.push_back(e);
    }
    {
        Enemy* e = NewGO<Enemy>(0, "enemy2");
        e->SetInitPos({ 100.0f, -100.0f, -1000.0f });
        e->Init();
        enemies.push_back(e);
    }
    {
        Enemy* e = NewGO<Enemy>(0, "enemy3");
        e->SetInitPos({ -100.0f, -100.0f, -1000.0f });
        e->Init();
        enemies.push_back(e);
    }

    return true;
}

void EnemyManager::Update()
{
    for (auto e : enemies) {
        e->Update();
    }
}

void EnemyManager::Render(RenderContext& rc)
{
    for (auto e : enemies) {
        e->Render(rc);
    }
}

