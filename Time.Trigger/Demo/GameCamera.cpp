#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera() = default;
GameCamera::~GameCamera() = default;

bool GameCamera::Init()
{
    // 初期カメラオフセット（注視点からカメラまでの距離）
    m_toCameraPos = Vector3(0.0f, 150.0f, 10.0f);

    // プレイヤーオブジェクトを検索
    m_player = FindGO<Player>("player");

    // カメラのニア・ファークリップ設定
    g_camera3D->SetNear(1.0f);
    g_camera3D->SetFar(10000.0f);

    return true;
}

void GameCamera::Update()
{
    if (!m_player) {
        return; // プレイヤーが見つからない場合は処理を終了
    }

    // プレイヤーの位置を取得
    Vector3 playerPosition = m_player->m_position;

    // カメラの初期注視点と位置
    Vector3 target = playerPosition;
    target.y += 200.0f; // プレイヤーの視線の高さを少し上に
    Vector3 cameraPosition = target + m_toCameraPos;

    // 右スティックの入力（カメラ回転用）
    float x = g_pad[0]->GetRStickXF(); // 水平回転 (Y軸)
    float y = g_pad[0]->GetRStickYF(); // 垂直回転 (X軸)

    // 水平方向の回転を計算
    Quaternion horizontalRotation;
    horizontalRotation.SetRotationDeg(Vector3::AxisY, 3.0f * x); // 右スティックX軸で回転

    // カメラの回転を反映
    horizontalRotation.Apply(m_toCameraPos);

    // 垂直方向の回転を制限（上下視点制限）
    Vector3 toPosDir = m_toCameraPos;
    toPosDir.Normalize();
    if (toPosDir.y < -0.5f) {
        m_toCameraPos.y = -0.5f;
    }
    else if (toPosDir.y > 0.5f) {
        m_toCameraPos.y = 0.5f;
    }

    // 左スティックの入力で移動
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();
    if (fabsf(stickL.x) > 0.001f || fabsf(stickL.y) > 0.001f) {
        // 左スティックの入力による前進・後退・左右移動
        Vector3 forward = g_camera3D->GetForward();
        Vector3 right = g_camera3D->GetRight();
        forward.y = 0.0f; // Y軸方向は移動させない
        right.y = 0.0f; // Y軸方向は移動させない

        forward.Normalize();
        right.Normalize();

        forward *= stickL.y * 240.0f;
        right *= stickL.x * 240.0f;

        Vector3 moveSpeed = forward + right;
        m_player->m_position = m_player->m_characterController.Execute(moveSpeed, 1.0f / 60.0f);
    }

    // プレイヤーのモデルも右スティックの回転を反映
    Quaternion playerRotation = m_player->rotation;
    playerRotation = horizontalRotation * playerRotation;
    m_player->rotation = playerRotation;

    // モデルレンダラーに回転を反映
    m_player->m_modelRender.SetRotation(playerRotation);

    // カメラの位置を計算
    cameraPosition = target + m_toCameraPos;

    // メインカメラに注視点と視点を設定
    g_camera3D->SetTarget(target);
    g_camera3D->SetPosition(cameraPosition);

    // カメラを更新
    g_camera3D->Update();
}
