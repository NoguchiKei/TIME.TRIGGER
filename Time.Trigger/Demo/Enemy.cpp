#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() {}
Enemy::~Enemy() {}

void Enemy::SetInitPos(const Vector3& pos)
{
    m_initPos = pos;
    m_position = pos; 
}

bool Enemy::Init()
{

    m_modelRender.Init("Assets/modelData/Enemy/Enemy.tkm");
    m_modelRender.SetScale(3.0f, 3.0f, 3.0f);

    m_player = FindGO<Player>("player");

    m_characterController.Init(25.0f, 174.0f, m_position);

   // m_nvmMesh.Init("Assets/modelData/BackGround/SuperHot_Stage_1.tkn");
    m_nvmMesh.Init("Assets/modelData/BackGround/stage_01_navi.tkn");
    return true;
}



void Enemy::Update()
{
    Move();
    ManageState();
   
  
}

void Enemy::Move()
{
   // if (m_player == nullptr) return;

   // bool isEnd;
   // Vector3 toPlayer = m_player->m_position - m_position;
   // float distToPlayer = toPlayer.Length();

   // // プレイヤーとの距離で状態を分岐
   //// const float attackRange = 80.0f;   // 攻撃に切り替える距離
   // const float chaseRange = 3000.0f;  // 追跡開始距離

   // if (distToPlayer < chaseRange) {
   //     m_pathFiding.Execute(
   //         m_path,
   //         m_nvmMesh,
   //         m_position,
   //         m_player->m_position,
   //         PhysicsWorld::GetInstance(),
   //         50.0f,
   //         200.0f

   //     );


   //     // ナビメッシュ経路に沿って移動
   //     m_position = m_path.Move(
   //         m_position,
   //         20.0f,   // 移動速度
   //         isEnd
   //     );

   //     // 前を向く
   //     Vector3 toPlayerDir = toPlayer;
   //     toPlayerDir.Normalize();
   //     m_enemyForward = toPlayerDir;
   // }

    if (m_characterController.IsOnGround()) {
        m_verticalSpeed = 0.0f;
    }
    else {
        m_verticalSpeed -= 15.0f;   // ← 重力
    }

    // 垂直方向の速度をセット
    m_moveSpeed = Vector3::Zero;
    m_moveSpeed.y = m_verticalSpeed;

    // 実際の移動（XZ の移動は上の AI の処理で m_position に直接入っているため Y だけ落とす）
    m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 45.0f);

    // 回転と描画を更新
    m_rotation.SetRotationY(atan2(m_enemyForward.x, m_enemyForward.z));
    m_modelRender.SetPosition(m_position);
    m_modelRender.SetRotation(m_rotation);
    m_modelRender.Update();
}

void Enemy::ManageState()
{
    switch (m_enemyState)
    {
    case 0: // 待機
        // 待機モーション

        break;
    case 1: // 死亡
        m_isAlive = false;
 
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

//if (distToPlayer > attackRange) {
//    // ========== 追跡モード ==========
//    m_pathFiding.Execute(
//        m_path,
//        m_nvmMesh,
//        m_position,
//        m_player->m_position,
//        PhysicsWorld::GetInstance(),
//        50.0f,
//        200.0f
//
//    );
//
//
//    // ナビメッシュ経路に沿って移動
//    m_position = m_path.Move(
//        m_position,
//        20.0f,   // 移動速度
//        isEnd
//    );
//
//    // 前を向く
//    Vector3 toPlayerDir = toPlayer;
//    toPlayerDir.Normalize();
//    m_enemyForward = toPlayerDir;
//}
//else {
//    // ========== 攻撃モード ==========
//    // ここで銃撃処理（アニメーション再生や弾発射など）を書く
//    // 今回はまだ省略でOK
//}