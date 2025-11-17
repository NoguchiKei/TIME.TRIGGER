#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"

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
    // 例: 2体の敵を出すxc
    {
        Enemy* e = NewGO<Enemy>(0, "enemy1");
        e->SetInitPos({ 0.0f, 0.0f, 2200.0f });
        e->Init();
        enemies.push_back(e);
    }
    {
        Enemy* e = NewGO<Enemy>(0, "enemy2");
        e->SetInitPos({ 500.0f, 0.0f, 1800.0f });
        e->Init();
        enemies.push_back(e);
    }
 
    

    return true;
}

void EnemyManager::Update()
{
    // まず生きている敵だけ更新
    for (auto e : enemies)
    {
        if (!e->IsDead()) {
            e->Update();
        }
    }

    // 次に死亡した敵を削除
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        Enemy* e = *it;
        if (e->IsDead()) {
            it = enemies.erase(it);
            DeleteGO(e);
        }
        else {
            ++it;
        }
    }

	CheckCollision();//弾の判定

}

void EnemyManager::CheckCollision()
{
    // プレイヤーの弾と敵の当たり判定チェック
	if (m_player == nullptr) return;
    for (auto e : enemies) {
        // 敵が生きている場合のみ当たり判定をチェック
        if (!e->IsDead()) {
            // プレイヤーの弾リストを取得
            const auto& shots = m_player->GetShots();
            for (const auto& shot : shots) {
                // 弾がアクティブであれば当たり判定をチェック
                if (shot.active) {
                    float distance = (e->GetPosition() - shot.pos).Length();
                    if (distance < 300.0f) { // 当たり判定の閾値
                        e->OnHit(); // 敵にヒットを通知
                        break; // 1発の弾で複数回ヒットしないようにする
                    }
                }
            }
        }
	}
}

void EnemyManager::Render(RenderContext& rc)
{
    for (auto e : enemies) {
        e->Render(rc);
    }

   /* if (g_isHit) {
        g_hitFont.Draw(
            L"HIT!",
            { 640.0f, 360.0f },
            g_vec4Red,
            1.5f
        );
    }*/
}

