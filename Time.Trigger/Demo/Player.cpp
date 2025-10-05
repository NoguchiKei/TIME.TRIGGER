#include "stdafx.h"
#include "Player.h"

Player::Player() {}
Player::~Player() {}

bool Player::Init()
{
    // プレイヤーモデルの読み込み
    m_modelRender.Init("Assets/modelData/Player/Player2.tkm");
    //m_modelRender.SetScale(3.0f, 3.0f, 3.0f);
    m_position = { 0,100,0 };
    // キャラクターコントローラー（当たり判定）の初期化
    m_characterController.Init(25.0f, 75.0f, m_position);

    return true;
}

bool Player::ShotInit()
{
    m_bulletModel.Init("Assets/modelData/Player/Tama.tkm");
    m_shots.clear();
    m_timer = 0.0f;
    return true;
     
}

void Player::Update()
{
    Move();
    ManageState();
    ShotUpdate();
    m_modelRender.Update();
}

void Player::Move()
{
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.z = g_pad[0]->GetLStickYF();

    Vector3 forward = g_camera3D->GetForward();
    forward.y = 0.0f;
    forward.Normalize();

    Vector3 right = g_camera3D->GetRight();
    right.y = 0.0f;
    right.Normalize();

    moveSpeed = right * (stickL.x * 120.0f) + forward * (stickL.z * 120.0f);

    if (m_characterController.IsOnGround())
    {
        m_verticalSpeed = 0.0f;
        if (g_pad[0]->IsTrigger(enButtonA))
            m_verticalSpeed = 500.0f;
    }
    else
    {
        m_verticalSpeed -= 15.0f;
    }

    moveSpeed.y = m_verticalSpeed;
    m_position = m_characterController.Execute(moveSpeed, 1.0f / 45.0f);
    m_modelRender.SetPosition(m_position);
}

void Player::ManageState()
{
    //地面に付いていなかったら。
    if (m_characterController.IsOnGround() == false)
    {
        //ステートを1(ジャンプ中)にする。
        playerState = 1;
        //ここでManageStateの処理を終わらせる。
        return;
    }

    //地面に付いていたら。
    //xかzの移動速度があったら(スティックの入力があったら)。
    if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
    {
        //ステートを2(歩き)にする。
        playerState = 2;
    }
    //xとzの移動速度が無かったら(スティックの入力が無かったら)。
    else
    {
        //ステートを0(待機)にする。
        playerState = 0;
    }
}

void Player::ShotUpdate()
{
    if (m_timer > 0.0f) m_timer -= 1.0f / 60.0f;

    if (g_pad[0]->IsTrigger(enButtonB) && m_timer <= 0.0f)
    {
        Shot b;
        b.pos = m_position + Vector3(0, 180, 0);//発射位置
        b.startPos = b.pos;
        b.dir = g_camera3D->GetForward();
        b.dir.y = 0;
        b.dir.Normalize();
        b.active = true;
        m_shots.push_back(b);

        m_timer = m_shotInterval;
    }

    float speed = 1000.0f * (2.0f / 60.0f);
    for (auto& b : m_shots)
    {
        if (!b.active) continue;
        b.pos += b.dir * speed;
        if ((b.pos - b.startPos).Length() >= 1200.0f) b.active = false;
    }

    m_shots.erase(
        std::remove_if(m_shots.begin(), m_shots.end(),
            [](const Shot& b) { return !b.active; }),
        m_shots.end()
    );
}

void Player::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);

    for (auto& b : m_shots)
    {
        m_bulletModel.SetPosition(b.pos);
        m_bulletModel.Update();
        m_bulletModel.Draw(rc);
    }
}
