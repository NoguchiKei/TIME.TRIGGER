#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy() {}
Enemy::~Enemy() {}

void Enemy::SetInitPos(const Vector3& pos)
{
    m_initPos = pos;
    m_position = pos; // ������ m_position �ɂ��R�s�[
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
    // �ړ� �i�r���b�V���Ȃǂ��g���Ď���
    //10���R���܂łɎ���
}

void Enemy::ManageState()
{
    switch (m_enemyState)
    {
    case 0: // �ҋ@
        // �ҋ@���[�V����

        break;
    case 1: // ���S
        m_respawnTimer += g_gameTime->GetFrameDeltaTime();
        if (m_respawnTimer >= 5.0f) { // 5�b��ɕ���
            m_isAlive = true;
            m_position = m_initPos; // �����ʒu�ɖ߂�
            m_characterController.SetPosition(m_position);
            m_enemyState = 0; // �ҋ@��Ԃɖ߂�
        }
        break;
    case 2: // �U��

        // �U�����[�V����
        break;
    case 3: // �ǐ�


        // �ǐՃ��[�V����

        break;
    default:
        // �s���ȏ��
        if (!m_isAlive) {
            m_enemyState = 1; // ���S
            m_respawnTimer = 0.0f;
        }
        break;

    }
}

void Enemy::OnHit()
{
    if (m_isAlive) {
        m_isAlive = false;
        m_enemyState = 1; // ���S��ԂɕύX
        m_respawnTimer = 0.0f;
    }
}

void Enemy::Render(RenderContext& rc)
{
    if (m_isAlive) {
        m_modelRender.Draw(rc);
    }
}
