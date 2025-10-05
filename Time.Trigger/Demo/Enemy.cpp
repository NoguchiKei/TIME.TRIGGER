#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy() {}
Enemy::~Enemy() {}

void Enemy::SetInitPos(const Vector3& pos)
{
    m_initPos = pos;
    m_position = pos; // ここで m_position にもコピー
}

bool Enemy::Init()
{

    m_modelRender.Init("Assets/modelData/Enemy/Enemy.tkm");
    m_modelRender.SetScale(3.0f, 3.0f, 3.0f);

    m_characterController.Init(25.0f, 75.0f, m_position);
    return true;
}



void Enemy::Update()
{



    Move();
    ManageState();
    m_modelRender.Update();
}

void Enemy::Move()
{
    // 移動 ナビメッシュなどを使って実装
    //10月３日までに実装
}

void Enemy::ManageState()
{
    switch (m_enemyState)
    {
    case 0: // 待機
        // 待機モーション

        break;
    case 1: // 死亡
        m_respawnTimer += g_gameTime->GetFrameDeltaTime();
        if (m_respawnTimer >= 5.0f) { // 5秒後に復活
            m_isAlive = true;
            m_position = m_initPos; // 初期位置に戻す
            m_characterController.SetPosition(m_position);
            m_enemyState = 0; // 待機状態に戻る
        }
        break;
    case 2: // 攻撃

        // 攻撃モーション
        break;
    case 3: // 追跡


        // 追跡モーション

        break;
    default:
        // 不明な状態
        if (!m_isAlive) {
            m_enemyState = 1; // 死亡
            m_respawnTimer = 0.0f;
        }
        break;

    }
}

void Enemy::OnHit()
{
    if (m_isAlive) {
        m_isAlive = false;
        m_enemyState = 1; // 死亡状態に変更
        m_respawnTimer = 0.0f;
    }
}

void Enemy::Render(RenderContext& rc)
{
    if (m_isAlive) {
        m_modelRender.Draw(rc);
    }
}
